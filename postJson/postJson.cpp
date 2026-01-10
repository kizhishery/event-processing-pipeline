#include "postJson.hpp"

#include <iostream>
#include <curl/curl.h>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

static std::pair<std::string, std::string> getEnv() {
    const char* url = std::getenv("URL");
    if (!url || !*url)
        throw std::runtime_error("URL env var not set");

    const char* key = std::getenv("KEY");
    if (!key || !*key)
        throw std::runtime_error("KEY env var not set");

    return std::make_pair(std::string(url), std::string(key));
}


void postJson(const json& payload) {
    auto [URL, KEY] = getEnv();

    CURL* curl = curl_easy_init();
    if (!curl)
        throw std::runtime_error("Failed to init curl");

        
    struct curl_slist* headers = nullptr;
    
    std::string body = payload.dump();
    std::string authHeader = "Authorization: Bearer " + KEY;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, authHeader.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
        throw std::runtime_error(curl_easy_strerror(res));
}
