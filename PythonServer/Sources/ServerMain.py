from Sources.ServerSources.Server import Server
import socket

if __name__ == "__main__":
    s = Server('localhost', 9090)
    s.accept_clients()

    # simple Client
    """sock = socket.socket()
    sock.connect(('localhost', 9090))
    sock.send(bytes("hello", "utf8"));

    data = sock.recv(1024)
    sock.close()

    print(data)"""

