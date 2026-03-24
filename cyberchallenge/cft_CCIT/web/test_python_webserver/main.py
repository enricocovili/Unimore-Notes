from fastapi import FastAPI, Request
from fastapi.middleware.cors import CORSMiddleware
import uvicorn
import os
import time
from fastapi.responses import FileResponse

app = FastAPI()

# Disable CORS
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=False,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.middleware("http")
async def log_requests(request: Request, call_next):
    os.system("clear" if os.name != "nt" else "cls")
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
    print(f"Method: {request.method}")
    print(f"URL: {request.url}")
    print(f"Headers: {dict(request.headers)}")
    print(f"Cookies: {dict(request.cookies)}")
    print(f"Query Params: {dict(request.query_params)}")

    body = await request.body()
    if body:
        print(f"Body: {body.decode()}")

    response = await call_next(request)
    print(f"Status Code: {response.status_code}\n")
    return response


@app.get("/")
async def root():
    return {"message": "Hello World"}


@app.get("/jpasta")
async def buy_a_flag():
    return FileResponse("jpasta.html", media_type="text/html")


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
