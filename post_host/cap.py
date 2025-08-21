from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class Handler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        content_type = self.headers['Content-Type']
        boundary = content_type.split("boundary=")[-1].encode()

        # Read the raw POST data
        body = self.rfile.read(content_length)

        # Split by boundary
        parts = body.split(b"--" + boundary)
        for part in parts:
            if b"Content-Disposition" in part and b"filename=" in part:
                headers, filedata = part.split(b"\r\n\r\n", 1)
                filedata = filedata.rsplit(b"\r\n", 1)[0]

                # Extract filename
                header_str = headers.decode(errors="ignore")
                filename_marker = 'filename="'
                filename = header_str.split(filename_marker)[-1].split('"')[0]

                # Save file
                with open(filename, "wb") as f:
                    f.write(filedata)
                print(f"[+] Saved {filename} ({len(filedata)} bytes)")

        self.send_response(200)
        self.end_headers()
        self.wfile.write(b"Upload OK")

if __name__ == "__main__":
    host, port = "127.0.0.1", 8080
    server = HTTPServer((host, port), Handler)
    print(f"[*] Listening on http://{host}:{port}")
    os.makedirs(".", exist_ok=True)
    server.serve_forever()
