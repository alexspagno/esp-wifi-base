const String htmlHead = R"------(
<!DOCTYPE html>
<html>
<head>
    <title>SETUP WIFI</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            background-color: #f7f7f7;
            margin: 0;
            padding: 0;
            padding-top: 20px;
            padding-left: 20px;
        }

        h1 {
            color: #333;
        }
        h3 {
            color: #5F9EA0;
        }

        #countdown {
            font-size: 26px;
            color: #5F9EA0;
        }

        p {
            margin-top: 20px;
        }

        table {
            width: auto;
            margin: 0;
            border-collapse: collapse;
            background-color: white;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }

        th, td {
            padding: 12px;
            text-align: left;
            border-bottom: 1px solid #ddd;
        }

        th {
            background-color: #f2f2f2;
        }

        tr:hover {
            background-color: #e0e0e0;
        }

        input[type="radio"] {
            vertical-align: middle;
        }
    </style>
</head>
<body>
    
)------";


const String htmlScan = R"------(
    <p id="countdown"></p>
    <script>
        function countdown() {
            var dots = "";
            var countdownElement = document.getElementById("countdown");

            function updateCountdown() {
                dots += ".";
                countdownElement.innerHTML = "Network scan" + dots;
                if (dots.length < 10) {
                    setTimeout(updateCountdown, 1000);
                } else {                    
                    window.location.href = "/setupwifi";
                }
            }            
            updateCountdown();
        }
        window.onload = countdown;
    </script>
</body>
</html>
)------";


const String htmlConnect = R"------(
    <p id="countdown"></p>
    <script>
        function countdown() {
            var dots = "";
            var countdownElement = document.getElementById("countdown");

            function updateCountdown() {
                dots += ".";
                countdownElement.innerHTML = "Try to connect" + dots;
                if (dots.length < 15) {
                    setTimeout(updateCountdown, 1000);
                } else {                    
                    window.location.href = "/setupwifi";
                }
            }            
            updateCountdown();
        }
        window.onload = countdown;
    </script>
</body>
</html>
)------";
