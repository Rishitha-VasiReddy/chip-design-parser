
# **Chip Design Parsing Tool** 🖥️  


A powerful tool designed to streamline chip design workflows by parsing Verilog files, identifying key components, optimizing designs, and presenting actionable insights through an intuitive front-end and REST API.

---

## **📜 Overview**

Modern chip design involves managing complex Verilog files, detecting inefficiencies, and visualizing key elements. This tool automates the process by:
- Parsing Verilog files to extract modules, inputs, outputs, wires, and assignments.
- Storing parsed components in an **SQLite database** for efficient querying.
- Exposing a **REST API** for data access.
- Visualizing components in a user-friendly **front-end** interface.

---

## **🚀 Features**
- **📄 Verilog Parser**: Automatically extracts key design components like modules, inputs, outputs, wires, and assignments.
- **📊 Database Integration**: Stores parsed components in an SQLite database for persistent storage.
- **🛠️ Optimization Suggestions**: Detects unused wires and provides actionable improvement insights.
- **🌐 REST API**: Exposes parsed data via Flask for integration with other systems.
- **📈 Front-End Visualization**: Interactive web-based visualization of parsed chip components.

---

## **🎯 Use Cases**
- **Chip Designers**: Quickly validate Verilog files for errors or inefficiencies.
- **Developers**: Build additional tools by integrating the REST API.
- **Students**: Learn and experiment with chip design and optimization.

---

## **🛠️ Technology Stack**

| **Component**        | **Technology**                  |
|-----------------------|---------------------------------|
| Verilog Parsing       | **C++**                        |
| Database              | **SQLite**                     |
| REST API              | **Flask (Python)**             |
| Front-End Interface   | **HTML/JavaScript**            |
| Hosting (Local Dev)   | **Python HTTP Server**         |

---

## **📂 Project Structure**
```
chip_design_tool/
├── build/                 # Compiled binaries
├── src/                   # Source code files
│   ├── main.cpp           # C++ backend logic
├── chip_design.db         # SQLite database (auto-created)
├── design.v               # Example Verilog file
├── app.py                 # Flask REST API
├── index.html             # Front-end visualization
└── README.md              # Project documentation
```

---

## **🚀 Getting Started**

### **1. Prerequisites**
Ensure you have the following installed:
- **Python 3** with Flask and Flask-CORS:
  ```bash
  pip3 install flask flask-cors
  ```
- **g++ Compiler** with C++11 support.
- **SQLite3**.

---

### **2. Setup Instructions**

#### Clone the Repository:
```bash
git clone https://github.com/username/chip-design-tool.git
cd chip_design_tool
```

#### Compile the C++ Backend:
```bash
g++ -std=c++11 -o build/chip_tool src/main.cpp -lsqlite3 -lpthread
```

#### Parse the Verilog File:
```bash
./build/chip_tool design.v
```

#### Start the Flask REST API:
```bash
python3 app.py
```

#### Start the Front-End Server:
```bash
python3 -m http.server 8000
```

#### Access the Front-End:
Open your browser and go to:
```
http://localhost:8000
```

---

## **🌐 REST API Endpoints**

### **GET /report**
Fetches all parsed components as a JSON object.

#### Example Request:
```bash
curl http://localhost:8080/report
```

#### Example Response:
```json
[
    {"Type": "Module", "Name": "example"},
    {"Type": "Input", "Name": "clk"},
    {"Type": "Output", "Name": "reset"},
    {"Type": "Wire", "Name": "data"},
    {"Type": "Assign", "Name": "data = clk & reset"}
]
```

---

## **📊 Example Outputs**

### **1. Console Output (Backend)**
```
Database initialized successfully!
Module definition found: example
Input definition found: clk
Output definition found: reset
Wire definition found: data
Assign statement found: data = clk & reset
End of module found.
```

### **2. Front-End Output**

```
Parsed Components
- Module: example
- Input: clk
- Output: reset
- Wire: data
- Assign: data = clk & reset
```

---

## **📂 Example Verilog File**
```verilog
module example;
input clk;
output reset;
wire data;
assign data = clk & reset;
endmodule
```

---

## **💡 Future Enhancements**
1. **Advanced Verilog Support**:
   - Add support for additional constructs like parameters, generate blocks, etc.
2. **Interactive Front-End**:
   - Introduce search, filtering, and sorting functionality.
   - Use modern front-end frameworks like **React** or **Vue.js**.
3. **Comprehensive Optimization**:
   - Identify unused modules and optimize complex assignments.
4. **Real-Time Collaboration**:
   - Enable multiple users to collaborate on chip design analysis.

---

## **🤝 Contributing**
We welcome contributions to improve the project! To contribute:
1. Fork the repository.
2. Create a new branch for your feature:
   ```bash
   git checkout -b feature-name
   ```
3. Commit and push your changes:
   ```bash
   git commit -m "Add new feature"
   git push origin feature-name
   ```
4. Submit a pull request.




