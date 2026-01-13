#!/usr/bin/env python3
import http.server
import socketserver
import socket
import webbrowser
import threading
import os

class MyHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Cache-Control', 'no-cache, no-store, must-revalidate')
        self.send_header('Pragma', 'no-cache')
        self.send_header('Expires', '0')
        super().end_headers()

    def do_GET(self):
        # Redirigir la raíz a index.html si existe
        if self.path == '/':
            self.path = '/index.html'
        return super().do_GET()

def get_local_ip():
    """Obtener la IP local de la máquina"""
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
        s.close()
        return ip
    except:
        return "127.0.0.1"

def start_server(port=8000):
    """Iniciar servidor HTTP"""
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    
    handler = MyHTTPRequestHandler
    try:
        with socketserver.TCPServer(("", port), handler) as httpd:
            local_ip = get_local_ip()
            
            print("=" * 60)
            print("🚀 SERVIDOR DE SIMULACIÓN INICIADO")
            print("=" * 60)
            print(f"📂 Directorio: {os.getcwd()}")
            print(f"📍 Local:      http://localhost:{port}")
            print(f"🌐 Red Local:  http://{local_ip}:{port}")
            print("=" * 60)
            print("📱 Para acceder desde otros dispositivos:")
            print(f"   1. Conéctate a la MISMA red WiFi")
            print(f"   2. Abre navegador y ve a: http://{local_ip}:{port}")
            print("=" * 60)
            print("🛑 Presiona Ctrl+C para detener el servidor")
            print("=" * 60)
            
            # Abrir automáticamente en el navegador local
            try:
                webbrowser.open(f'http://localhost:{port}')
            except:
                pass
            
            httpd.serve_forever()
    except KeyboardInterrupt:
        print("\n🛑 Servidor detenido")
    except OSError as e:
        print(f"❌ Error al iniciar servidor: {e}")
        print("💡 Posibles causas: Puerto ocupado o permisos insuficientes.")
        print("💡 Intenta cambiar el puerto (ej. start_server(8080))")

if __name__ == "__main__":
    start_server(8000)