#ifndef NETCLIENT_NET_CLIENT_H
#define NETCLIENT_NET_CLIENT_H

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

namespace olc{
    namespace net{

        template<typename T>
        class Client_interface{

        public:

            Client_interface() : m_socket(m_context){
               // Initialize the socket with the io context, so it can do staff
            }

            virtual ~Client_interface(){
                // If the client is destroyed, always try and disconnect from server
                disconnect();
            }

            // Connection to server with hostname/ip-address and port
            bool connect(const std::string& host, const uint16_t port){

                try{

                    // Create connection
                    m_connection = std::make_unique<Connection<T>>();

                    // Resolve hostname/ip-address into tangiable phisical address
                    asio::ip::tcp::resolver resolver(m_context);
                    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

                    // Tell the connection object to connect to server
                    m_connection->connectToServer(endpoints);

                    // Start context Thread
                    thrContext = std::thread([this](){ m_context.run(); } );

                }catch(std::exception& e){
                    std::cerr << "Client exception " << e.what() << "\n";
                    return false;
                }

                return true;
            }

            // Disconnect from server
            void disconnect(){

            }

            // Check if client is actually connected to a server
            bool isConnected(){
                if (m_connection)
                    return m_connection->isConnected();
                else
                    return false;
            }

            // Retrieve queue of message from server
            Tsqueue<Owned_message<T>>& incoming(){
                return m_qMessagesIn;
            }

        protected:
            // Asio context handles the data transfer
            asio::io_context m_context;

            // ... but needs a thread of its own to execute its work commands
            std::thread thrContext;

            // This is the hardware socket that is connected to the server
            asio::ip::tcp::socket m_socket;

            // The client has a single instance of a "connection" object, witch handles data transfer
            std::unique_ptr<Connection<T>> m_connection;

        private:
            // This is the thread save queue of incoming messages from server
            Tsqueue<Owned_message<T>>& m_qMessagesIn;
        };

    }
}

#endif //NETCLIENT_NET_CLIENT_H
