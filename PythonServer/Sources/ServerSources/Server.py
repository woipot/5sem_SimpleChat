import socket
import sys
import datetime
from Sources.ServerSources.Client import Client
from threading import Thread
from colorama import Fore


class Server:
    BUFSIZE = 1024

    clients = []

    def __init__(self, host, port):
        try:
            self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.host = host
            self.port = port
            self.server.bind((host, port))
            self.server.listen(5)
        except Exception as ex:
            print(Fore.RED + "#Error: Can't open socket %s" % ex)

    def accept_clients(self):
        print(Fore.BLUE + "#Info: Server was stated -> Listening on %s:%s" % (self.host, self.port))
        while True:
            try:
                (client_socket, address) = self.server.accept()
                print(Fore.GREEN + "#Info: new client was founded")
                client = Client(client_socket, address)
                # Adding client to clients list
                self.clients.append(client)

                # Client Connected
                self.validate_user(client)

                # Receiving data from client
                Thread(target=self.process_client, args=(client,)).start()
            except Exception as ex:
                print(Fore.RED + "#Error: can't accept client: %s" % ex)

    def process_client(self, client: Client):
        try:
            while True:
                msg = client.socket.recv(self.BUFSIZE)
                decoded_msg = msg.decode(encoding='utf-8')
                if decoded_msg != '':
                    self.on_message(client, decoded_msg)

                elif decoded_msg != {quit}:
                    self.on_close(client)
                    break

        except Exception as ex:
            print(Fore.RED + "#Error: %s in user -> %s" % (ex, client.address))
            self.close_client(client)

        print(Fore.GREEN + "#Info: client-> %s : %s disconnect from server (%s)"
              % (client.socket, client.address, client.screen_name))

    def broadcast(self, message: str):
        # Sending message to all clients
        for client in self.clients:
            client.send(message)

    def validate_user(self, client: Client):
        print(Fore.GREEN + "#Info: Client accepted %s %s" % (client.socket, client.address))

    def on_message(self, client: Client, message):
        today = datetime.datetime.today()
        processed_msg = "[%s]<%s>: %s" % (today.strftime("%Y/%m/%d %H.%M"), client.screen_name, message)
        self.broadcast(processed_msg)

    def on_close(self, client: Client):
        client.send("{quit}")
        self.close_client(client)

    def close_client(self, client: Client):
        client.socket.close()
        self.clients.remove(client)
        self.broadcast("-----#Info <>: %s has left the chat.-----" % client.screen_name)
