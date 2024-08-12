// Assuming clientSend is the function that handles the connection
int clientSend(char* SERVER);

int main() {
    char* SERVER = "localhost"; // Replace with your server address
    clientSend(SERVER);
    return 0;
}