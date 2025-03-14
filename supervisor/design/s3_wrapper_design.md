# S3 Wrapper.
This document explains the design of an S3 wrapper that enables uploading files to Amazon S3 using multipart upload while supporting authentication via AWS Signature Version 4 (SigV4). The wrapper abstracts the complexities of S3's multipart upload process, providing a streamlined interface for clients to handle large file uploads efficiently and securely.
Purpose

Multipart upload is essential when dealing with large files, as it allows a file to be split into smaller parts and uploaded in parallel, improving upload reliability and speed. The S3 wrapper handles:

- Initiating multipart uploads.
- Uploading individual parts.
- Completing the upload once all parts are successfully transferred.
- Handling retries for failed parts.
- Generating AWS SigV4 signed requests for secure communication with S3.

Key Features

- AWS SigV4 Authentication: Ensures all requests are securely signed, allowing authenticated and authorized access to S3.
- Parallel Part Uploads: Supports concurrent uploading of parts to optimize performance.
- Resumable Uploads: Provides the ability to resume failed or interrupted uploads.
- Configurable Part Size: Allows dynamic adjustment of part sizes based on file size and network conditions.
- Progress Tracking: Optional hooks for monitoring upload progress.


# Note on S3 Signature validation
```python 
from flask import Flask, request, abort
import hashlib
import hmac
import datetime

app = Flask(__name__)

AWS_SECRET_KEY = "YOUR_SECRET_KEY"
AWS_REGION = "us-east-1"
AWS_SERVICE = "s3"

def sign(key, msg):
    return hmac.new(key, msg.encode('utf-8'), hashlib.sha256).digest()

def get_signature_key(secret_key, date_stamp, region_name, service_name):
    k_date = sign(('AWS4' + secret_key).encode('utf-8'), date_stamp)
    k_region = sign(k_date, region_name)
    k_service = sign(k_region, service_name)
    k_signing = sign(k_service, 'aws4_request')
    return k_signing

@app.route('/validate', methods=['POST'])
def validate_request():
    headers = request.headers
    authorization_header = headers.get('Authorization')
    amz_date = headers.get('x-amz-date')
    host = headers.get('Host')
    
    if not authorization_header or not amz_date or not host:
        abort(400, "Missing required headers")

    # Parse the Authorization header
    # Example: AWS4-HMAC-SHA256 Credential=AKIA.../20250305/us-east-1/s3/aws4_request, SignedHeaders=host;x-amz-date, Signature=abcdef123456...
    try:
        auth_parts = dict(
            item.split('=') for item in authorization_header.replace('AWS4-HMAC-SHA256 ', '').replace(' ', '').split(',')
        )
        credential_scope = auth_parts['Credential'].split('/')[1:5]
        incoming_signature = auth_parts['Signature']
        signed_headers = auth_parts['SignedHeaders']
    except Exception as e:
        abort(400, f"Invalid Authorization header: {str(e)}")

    # Rebuild canonical request
    payload_hash = hashlib.sha256(request.get_data()).hexdigest()
    canonical_headers = f"host:{host}\n" + f"x-amz-date:{amz_date}\n"
    canonical_request = "\n".join([
        request.method,
        request.path,
        '',  # Query string if any
        canonical_headers,
        signed_headers,
        payload_hash
    ])
    hashed_canonical_request = hashlib.sha256(canonical_request.encode('utf-8')).hexdigest()

    # Build string to sign
    date_stamp = credential_scope[0]
    credential_scope_str = "/".join(credential_scope)
    string_to_sign = "\n".join([
        "AWS4-HMAC-SHA256",
        amz_date,
        credential_scope_str,
        hashed_canonical_request
    ])

    # Derive signing key and compute signature
    signing_key = get_signature_key(AWS_SECRET_KEY, date_stamp, AWS_REGION, AWS_SERVICE)
    computed_signature = hmac.new(signing_key, string_to_sign.encode('utf-8'), hashlib.sha256).hexdigest()

    if computed_signature != incoming_signature:
        abort(403, "Signature does not match!")

    return "Signature is valid!", 200

if __name__ == '__main__':
    app.run(port=5000)

```