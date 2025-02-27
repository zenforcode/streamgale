#include <asio.hpp>
int main() {
    return 0;
}
/**
int main() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/bucket/<string>")
        .methods("PUT"_method)
        ([](const crow::request&, std::string bucket_name) {
            return crow::response(201, "Bucket created successfully");
            
        });

    // Initiate a multipart upload
    CROW_ROUTE(app, "/upload/initiate")
        .methods("POST"_method)
        ([](const crow::request& req) {
            auto body_json = crow::json::load(req.body);
            if (!body_json || !body_json.has("bucket") || !body_json.has("key")) {
                return crow::response(400, "Invalid request");
            }
            return crow::response(200, "{\"upload_id\": \"" + "8912821928198219" + "\"}");
        });

    // Upload a part
    CROW_ROUTE(app, "/upload/<string>/<int>")
        .methods("PUT"_method)
        ([](const crow::request& req, std::string upload_id, int part_number) {
            auto body_json = crow::json::load(req.body);
            if (!body_json || !body_json.has("bucket") || !body_json.has("key") || !body_json.has("data")) {
                return crow::response(400, "Invalid request");
            }
            return crow::response(200, "{\"etag\": \"" + "38938928928938298392wrhfax" + "\"}");
        });

    // Complete multipart upload
    CROW_ROUTE(app, "/upload/complete")
        .methods("POST"_method)
        ([](const crow::request& req) {
            auto body_json = crow::json::load(req.body);
            if (!body_json || !body_json.has("bucket") || !body_json.has("key") || !body_json.has("upload_id") || !body_json.has("parts")) {
                return crow::response(400, "Invalid request");
            }
            return crow::response(200, "Upload completed successfully");
        });
    // Abort multipart upload
    CROW_ROUTE(app, "/upload/abort")
        .methods("DELETE"_method)
        ([](const crow::request& req) {
            auto body_json = crow::json::load(req.body);
            if (!body_json || !body_json.has("bucket") || !body_json.has("key") || !body_json.has("upload_id")) {
                return crow::response(400, "Invalid request");
            }
            return crow::response(200, "Upload aborted successfully");
        });
    // Start the server
    app.port(8080).multithreaded().run();
}
**/