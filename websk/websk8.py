import asyncio
import websockets
import random

PORT = 5008

async def rng_server(websocket):
    while True:
        number = random.randint(0, 100)
        await websocket.send(str(number))
        await asyncio.sleep(1)

async def main():
    async with websockets.serve(rng_server, "localhost", PORT):
        print(f"WebSocket RNG server running on ws://localhost:{PORT}")
        await asyncio.Future()  # run forever

asyncio.run(main())