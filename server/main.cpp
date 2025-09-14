#include "crow/app.h"
#include "crow/common.h"
#include "crow/http_response.h"
#include "crow/mustache.h"
#include "crow/query_string.h"
#include <iostream>
#include <string>
#include <vector>

struct User
{
    std::string username;
    std::string password;
};

int main()
{
    crow::SimpleApp app;
    std::vector<User> users;

    CROW_ROUTE(app, "/")(
        []()
        {
            auto indexPage = crow::mustache::load_text("index.html");
            return indexPage;
        });

    CROW_ROUTE(app, "/form")(
        []()
        {
            auto formPage = crow::mustache::load_text("form.html");
            return formPage;
        });

    CROW_ROUTE(app, "/submitted_data")
        .methods(crow::HTTPMethod::Post)(
            [&users](const crow::request &req)
            {
                auto url_params = req.get_body_params();
                std::string uname =
                    url_params.get("uname") ? url_params.get("uname") : "";
                std::string pword =
                    url_params.get("pword") ? url_params.get("pword") : "";

                users.push_back(User({uname, pword}));

                for (int i = 0; i < users.size(); i++)
                {
                    std::cout << "User #" << i << std::endl;
                    std::cout << "Username: " << users[i].username << std::endl;
                    std::cout << "Password: " << users[i].password << std::endl;
                    std::cout << std::endl;
                }

                crow::response res;
                res.code = 302;
                res.set_header("Location", "/");
                return res;
            });

    CROW_ROUTE(app, "/users")(
        [&users]()
        {
            auto usersPage = crow::mustache::load("users.html");

            crow::mustache::context ctx;
            std::vector<crow::mustache::context> userCtxArray;

            for (int i = 0; i < users.size(); i++)
            {
				crow::mustache::context buff;
                buff["index"] = i + 1;
                buff["uname"] = users[i].username;
                buff["pword"] = users[i].password;
                userCtxArray.push_back(buff);
            }

            ctx["users"] = std::move(userCtxArray);
            return usersPage.render(ctx);
        });

    app.port(1800).multithreaded().run();
}
