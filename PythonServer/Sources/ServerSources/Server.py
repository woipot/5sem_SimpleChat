import socket
import sys
import datetime
import re
from Sources.ServerSources.Client import Client
from threading import Thread
from colorama import Fore


class Server:
    BUFSIZE = 1024
    COMMANDSIZE = 1

    commands = {
        'msg': '0',
        'validate': '1',
        'user_list': '2'
    }

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
                # Client Connected
                is_success_validate = self.validate_user(client)

                if not is_success_validate:
                    self.silent_close(client)
                    continue

                # Adding client to clients list
                self.clients.append(client)

                # Receiving data from client
                Thread(target=self.process_client, args=(client,)).start()
            except Exception as ex:
                print(Fore.RED + "#Error: can't accept client: %s" % ex)

    def process_client(self, client: Client):
        try:
            while True:
                b_cmd = client.socket.recv(self.COMMANDSIZE)
                decoded_cmd = b_cmd.decode(encoding='utf-8')

                if decoded_cmd == self.commands['msg']:
                    b_msg = client.socket.recv(self.BUFSIZE)
                    decoded_msg = b_msg.decode(encoding='utf-8')
                    self.on_message(client, decoded_msg)

                elif decoded_cmd != {quit}:
                    break

        except Exception as ex:
            print(Fore.RED + "#Error: %s in user -> %s" % (ex, client.address))
            self.close_client(client)

        print(Fore.GREEN + "#Info: client-> %s : %s disconnect from server (%s)"
              % (client.socket, client.address, client.screen_name))
        self.close_client(client)

    def broadcast(self, message: str):
        # Sending message to all clients
        for client in self.clients:
            client.send(message)

    def validate_user(self, client: Client):
        print(Fore.CYAN + "#Info: start validate")
        b_cmd = client.socket.recv(self.COMMANDSIZE)
        decoded_cmd = b_cmd.decode(encoding='utf-8')

        is_success = True

        if decoded_cmd == self.commands['validate']:
            b_user_name = client.socket.recv(self.BUFSIZE)
            username = b_user_name.decode(encoding='utf-8')

            validate_result = self.validate_username(username)
            is_unique = self.validate_to_unique(username)

            if validate_result and is_unique:
                today = datetime.datetime.today()
                processed_msg = '\t[%s] User <%s> joined the chat.' % (today.strftime("%Y/%m/%d %H.%M"), username)
                self.broadcast(processed_msg)

                print(Fore.YELLOW + '#Info: Client accepted %s %s' % (client.socket, client.address))

            elif not validate_result:
                client.send('Validate error (name verification)')
                is_success = False
            else:
                client.send('Validate error (name is not unique)')
                is_success = False
        else:
            client.send('Validate error (validate command)')
            is_success = False

        print(Fore.CYAN + '#Info: validate is: %s' % is_success)
        return is_success

    def on_message(self, client: Client, message):
        today = datetime.datetime.today()
        processed_msg = "[%s]<%s>: %s" % (today.strftime("%Y/%m/%d %H.%M"), client.screen_name, message)
        self.broadcast(processed_msg)

    def silent_close(self, client: Client):
        print(Fore.GREEN + "#Info: client-> %s : %s SILENT disconnect from server (%s)"
              % (client.socket, client.address, client.screen_name))
        client.socket.close()
        if client in self.clients:
            self.clients.remove(client)

    def close_client(self, client: Client):
        client.socket.close()
        self.clients.remove(client)

        today = datetime.datetime.today()
        processed_msg = '\t[%s] User <%s> has left the chat.' % (today.strftime("%Y/%m/%d %H.%M"), client.screen_name)
        self.broadcast(processed_msg)

    @staticmethod
    def validate_username(name: str):
        result = bool(re.match(r"^[a-z|A-Z|_]{1}[a-z|A-Z|0-9|-|_]{3,19}$", name))
        return result

    def validate_to_unique(self, name: str):
        for client in self.clients:
            if client.screen_name == name:
                return False
        return True
