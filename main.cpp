#include <iostream>
#include <curl/curl.h>

size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    size_t newLength = size * nmemb;
    buffer->append((char*)contents, newLength);
    return newLength;
}

void fetch_url(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Fetched content from " << url << ":\n" << response.substr(0, 500) << "...\n";
        }

        curl_easy_cleanup(curl);
    }
}

int main() {
    std::string url = "http://example.com";
    fetch_url(url);
    return 0;
}
