#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>
namespace asio  = boost::asio;
namespace beast = boost::beast;
using tcp       = asio::ip::tcp;

int main() {
    try {
        asio::io_context io_context;

        // 解析URL
        const std::string url    = "snowflake.qq.com";
        const std::string target = "/ola/android";
        const std::string host   = url;
        const std::string port   = "443";

        // 创建SSL上下文
        asio::ssl::context ssl_context(asio::ssl::context::tlsv12_client);
        ssl_context.set_default_verify_paths();
        asio::ssl::stream<tcp::socket> socket(io_context, ssl_context);

        // 连接服务器
        tcp::resolver resolver(io_context);
        asio::connect(socket.next_layer(), resolver.resolve(host, port));
        socket.handshake(asio::ssl::stream_base::client);

        // 构建HTTP请求
        beast::http::request<beast::http::string_body> req(beast::http::verb::post,
                                                           target, 11);
        req.set(beast::http::field::host, host);
        req.set(beast::http::field::content_type, "application/json");
        req.body() = "{\"extra\":\"\"}";

        // 发送HTTP请求
        beast::http::write(socket, req);

        // 接收HTTP响应
        beast::flat_buffer                              buffer;
        beast::http::response<beast::http::string_body> res;
        beast::http::read(socket, buffer, res);

        if(res.result() == beast::http::status::ok) {
            // 处理响应数据
            std::string response_body = res.body();
            // 在此处解析响应数据和提取q16和q36
        } else {
            std::cerr << "HTTP请求失败，状态码：" << res.result_int() << std::endl;
        }
    } catch(const std::exception& e) {
        std::cerr << "HTTP请求错误：" << e.what() << std::endl;
    }

    return 0;
}
