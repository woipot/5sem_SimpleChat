class Client:
    def __init__(self, socket, address):
        self.socket = socket
        self.address = address
        self.screen_name = None


    # Send message to Client
    def send(self, data: str):
        self.socket.send(data.encode('utf-8'))

    def set_name(self, name):
        self.screen_name = name;
