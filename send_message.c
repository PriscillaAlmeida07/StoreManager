#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "send_message.h"

#define REMETENTE "email@gmail.com"
#define SENHA     ""
#define DESTINO   "email@gmail.com"

int enviar_email() {
    CURL *curl;
    CURLcode res;
    
    const char *mensagem =
        "To: " DESTINO "\r\n"
        "From: " REMETENTE "\r\n"
        "Subject: Teste de e-mail via C\r\n"
        "\r\n"
        "Olá, este é um teste de envio de e-mail via C!\r\n";

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Erro ao inicializar o CURL\n");
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
    curl_easy_setopt(curl, CURLOPT_USERNAME, REMETENTE);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, SENHA);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, REMETENTE);

    struct curl_slist *recipients = curl_slist_append(NULL, DESTINO);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, mensagem);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Erro ao enviar e-mail: %s\n", curl_easy_strerror(res));
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    return (res == CURLE_OK) ? 0 : 1;
}

