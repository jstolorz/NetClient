#ifndef NETCLIENT_NET_CONNECTION_H
#define NETCLIENT_NET_CONNECTION_H

#endif //NETCLIENT_NET_CONNECTION_H

namespace olc{
    namespace net{
        template<typename T>
        class Connection : public std::enable_shared_from_this<Connection<T>>{
        public:
            Connection(){}

            virtual ~Connection(){}

        public:
            bool connectToServer(const asio::ip::tcp::resolver::results_type& endpoints){


                return false;
            }


            bool disconnect();
            bool isConnected() const;
            bool send(const Message<T>& msg);

        protected:
            // Each Connection has a unique socket to remote
            asio::ip::tcp::socket m_socket;

            // This context is shared with the whole asio instance
            asio::io_context& m_asioContext;

            // This queue holds all messages to be sent to the remote side of this Connection
            Tsqueue<Message<T>> m_qMessagesOut;

            // This queue holds all message that have been received from
            // the remote side of this connection. Note it is a reference
            // as the "owner" of this connection is expected to provide a queue
            Tsqueue<Owned_message<T>>& m_qMessagesIn;

        };
    }
}
