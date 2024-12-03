from http.server import HTTPServer, BaseHTTPRequestHandler
import json

class CORSRequestHandler(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.send_header('Access-Control-Allow-Origin', '*')  # Allow requests from any origin
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')  # Allowed methods
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')  # Allowed headers
        self.end_headers()

    def do_OPTIONS(self):
        """Handle preflight requests"""
        self._set_headers()

    def do_POST(self):
        """Handle POST requests"""
        self._set_headers()
        content_length = int(self.headers['Content-Length'])  # Get the size of the data
        post_data = self.rfile.read(content_length)  # Read the data
        data = json.loads(post_data.decode('utf-8'))  # Decode JSON data
        print("Received data:", data)
        # Respond with a success message
        self.wfile.write(json.dumps({"message": "Data received successfully"}).encode('utf-8'))

def run(server_class=HTTPServer, handler_class=CORSRequestHandler, port=5000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting server on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()