# 🌟 Supervisor System

The **Supervisor** is a worker node responsible for autonomously executing assigned tasks. It dynamically manages available **CPU & GPU resources** and communicates with other system components. The Supervisor consists of three major components:

1. **Topology Server** – Provides real-time system topology and resource usage.  
2. **Membership Server** – Manages worker node registration and discovery.  
3. **Worker Monitor** – Tracks and reports worker health and performance.

Each component runs as a separate service within the **Supervisor**.

---

## 🚀 Requirements
Ensure the following dependencies are installed:

### ✅ Linux (Ubuntu/Debian)
```sh
sudo apt update
sudo apt install -y build-essential cmake git libasio-dev
```

### ✅ MacOS
```sh
brew install asio cmake git
```

### ✅ Windows
1. Install **CMake**: [Download here](https://cmake.org/download/)
2. Install **ASIO** manually:
   ```sh
   git clone https://github.com/chriskohlhoff/asio.git external/asio
   ```

---

## 🔄 Clone the Repository
Since **Crow** is a submodule, ensure recursive cloning:
```sh
git clone --recurse-submodules https://github.com/bcncpp/streamgale.git
cd supervisor
```
If you've already cloned the repo but forgot the submodules, run:
```sh
git submodule update --init --recursive
```

---

## 🛠️ Building the Supervisor and Its Components
1. **Create a Build Directory**
```sh
mkdir build && cd build
```

2. **Run CMake**
```sh
cmake ..
```

3. **Compile the Project**
```sh
make -j$(nproc)
```

---

## 🚀 Running the Supervisor and Its Components
Each component runs separately but integrates into the **Supervisor** system.

### Start the Supervisor
```sh
./supervisor
```
This launches all **sub-components**:  
✅ **Topology Server** (port: `18080`)  
✅ **Membership Server** (port: `18081`)  
✅ **Worker Monitor** (port: `18082`)  

### Start the Topology Server (Manually)
```sh
./toposerver
```
It runs on **`http://localhost:18080`** (configurable in `toposerver.cpp`).

---

## ❓ Troubleshooting
### CMake Can't Find ASIO?
- Check if ASIO is installed:
  ```sh
  ls -l /usr/include/asio.hpp
  ```
- If missing, manually install it:
  ```sh
  sudo apt install libasio-dev
  ```

### Undefined References When Linking?
- Ensure C++ standard matches:
  ```sh
  rm -rf build && mkdir build && cd build
  cmake -DCMAKE_CXX_STANDARD=20 ..
  make -j$(nproc)
  ```

### Crow Internal Header Not Found?
- Ensure submodules are initialized:
  ```sh
  git submodule update --init --recursive
  ```

---

## 📜 License
This project is licensed under the **MIT License**.

---

## 🎯 Contributing
1. Fork the repository.
2. Create a new branch (`feature-xyz`).
3. Commit your changes.
4. Push and open a **pull request**.

---

### 🚀 Happy Coding!
