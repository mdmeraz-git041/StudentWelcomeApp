
#include "crow.h"
#include <string>

using namespace std;

int main()
{
    crow::SimpleApp app;

    // 1. FRONTEND: Display the webpage
    CROW_ROUTE(app, "/")
    ([]()
    {
        return R"HTML(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>Student Welcome App</title>

    <!-- CSS: Styling the webpage -->
    <style>
        * {
            box-sizing: border-box;
        }

        body {
            font-family: Arial, sans-serif;
            background: #f0f4f8;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            margin: 0;
        }

        .container {
            background: white;
            padding: 35px;
            border-radius: 15px;
            box-shadow: 0 5px 20px #00000015;
            text-align: center;
            width: 90%;
            max-width: 400px;
        }

        h1 {
            color: #2563eb;
        }

        input {
            width: 100%;
            padding: 12px;
            margin: 15px 0;
            border: 1px solid #ccc;
            border-radius: 8px;
            font-size: 16px;
        }

        button {
            width: 100%;
            padding: 12px;
            background: #2563eb;
            color: white;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            cursor: pointer;
        }

        button:hover {
            background: #1d4ed8;
        }

        #result {
            margin-top: 20px;
            color: #15803d;
        }
    </style>
</head>

<body>
    <div class="container">
        <h1>Student Welcome App</h1>

        <p>Enter your name below</p>

        <input
            type="text"
            id="nameInput"
            placeholder="Enter your name"
        >

        <button onclick="welcomeStudent()">
            Welcome
        </button>

        <h2 id="result"></h2>
    </div>

    <!-- JavaScript: Connecting to the C++ backend -->
    <script>
        async function welcomeStudent() {
            const name = document
                .getElementById("nameInput")
                .value.trim();

            const result = document.getElementById("result");

            if (name === "") {
                result.style.color = "red";
                result.textContent = "Please enter your name.";
                return;
            }

            result.style.color = "#15803d";
            result.textContent = "Loading...";

            try {
                const response = await fetch(
                    "/welcome?name=" + encodeURIComponent(name)
                );

                if (!response.ok) {
                    throw new Error("Request failed");
                }

                const message = await response.text();

                result.textContent = message;
            }
            catch (error) {
                result.style.color = "red";
                result.textContent =
                    "Could not connect to the server.";
            }
        }
    </script>
</body>
</html>
        )HTML";
    });

    // 2. BACKEND: Receive the name and return a message
    CROW_ROUTE(app, "/welcome")
    ([](const crow::request& req)
    {
        const char* name =
            req.url_params.get("name");

        string studentName =
            (name != nullptr && *name != '\0')
            ? name
            : "Student";

        return "Welcome, " + studentName +
               "! Your request was received.";
    });

    // 3. Start the server
    app.port(18080)
       .multithreaded()
       .run();

    return 0;
}