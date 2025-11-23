from flask import Flask, render_template_string
import threading
import asyncio
import websockets

app = Flask(__name__)

# Shared data for websocket messages
latest_data = {"value": 0}

# HTML template with Chart.js for high-tech graph
HTML = """
<!DOCTYPE html>
<html>
<head>
    <title>High-Tech WebSocket Graph</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
        body { background: #181818; color: #eee; font-family: 'Segoe UI', sans-serif; }
        #chart-container { width: 80vw; height: 60vh; margin: 40px auto; background: #222; border-radius: 16px; box-shadow: 0 0 32px #0ff4; }
    </style>
</head>
<body>
    <h2 style="text-align:center;">Live WebSocket Data</h2>
    <div id="chart-container">
        <canvas id="myChart"></canvas>
    </div>
    <div id="stats" style="text-align:center; margin-top:20px; font-size:1.2em; color:#0ff;">
        Most Recent: <span id="recent">-</span> |
        Max: <span id="max">-</span> |
        Min: <span id="min">-</span>
    </div>
    <script>
        const ctx = document.getElementById('myChart').getContext('2d');
        const data = {
            labels: [],
            datasets: [{
                label: 'WebSocket Value',
                data: [],
                borderColor: '#0ff',
                backgroundColor: 'rgba(0,255,255,0.1)',
                tension: 0.3,
                pointRadius: 3,
                pointBackgroundColor: '#0ff'
            }]
        };
        const config = {
            type: 'line',
            data: data,
            options: {
                scales: {
                    x: { ticks: { color: '#0ff' }, grid: { color: '#333' } },
                    y: { ticks: { color: '#0ff' }, grid: { color: '#333' } }
                },
                plugins: {
                    legend: { labels: { color: '#0ff' } }
                }
            }
        };
        const myChart = new Chart(ctx, config);

        async function fetchData() {
            while (true) {
                const resp = await fetch('/data');
                const json = await resp.json();
                const now = new Date().toLocaleTimeString();
                data.labels.push(now);
                data.datasets[0].data.push(json.value);
                // Update stats
                const values = data.datasets[0].data;
                const recent = values.length ? values[values.length - 1] : '-';
                const max = values.length ? Math.max(...values) : '-';
                const min = values.length ? Math.min(...values) : '-';
                document.getElementById('recent').textContent = recent;
                document.getElementById('max').textContent = max;
                document.getElementById('min').textContent = min;
                myChart.update();
                await new Promise(r => setTimeout(r, 500));
            }
        }
        fetchData();
    </script>
</body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(HTML)

@app.route('/data')
def get_data():
    return latest_data

# WebSocket listener in background thread
def websocket_listener():
    async def listen():
        uri = "ws://localhost:5001"
        async with websockets.connect(uri) as websocket:
            while True:
                msg = await websocket.recv()
                try:
                    val = float(msg)
                except ValueError:
                    val = 0
                latest_data["value"] = val
    asyncio.run(listen())

if __name__ == '__main__':
    threading.Thread(target=websocket_listener, daemon=True).start()
    app.run(debug=False, use_reloader=False)