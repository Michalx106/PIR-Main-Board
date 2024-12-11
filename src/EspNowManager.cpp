#include "EspNowManager.hpp"

EspNowManager::OnDataReceivedCallback EspNowManager::dataReceivedCallback = nullptr;
EspNowManager::OnDataSentCallback EspNowManager::dataSentCallback = nullptr;

EspNowManager::EspNowManager() {}

bool EspNowManager::begin() {
    // Ustawienie trybu Wi-Fi
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Błąd inicjalizacji ESP-NOW");
        return false;
    }
    // Rejestracja statycznych callbacków
    esp_now_register_recv_cb(handleDataReceived);
    esp_now_register_send_cb(handleDataSent);
    return true;
}

void EspNowManager::onReceive(OnDataReceivedCallback callback) {
    dataReceivedCallback = callback;
}

void EspNowManager::onSend(OnDataSentCallback callback) {
    dataSentCallback = callback;
}

bool EspNowManager::addPeer(const uint8_t *peerAddress) {
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Błąd dodawania odbiorcy");
        return false;
    }
    return true;
}

bool EspNowManager::sendData(const uint8_t *peerAddress, const uint8_t *data, size_t len) {
    esp_err_t result = esp_now_send(peerAddress, data, len);
    if (result != ESP_OK) {
        Serial.println("Błąd wysyłania danych");
        return false;
    }
    return true;
}

void EspNowManager::handleDataReceived(const uint8_t *macAddr, const uint8_t *data, int len) {
    if (dataReceivedCallback) {
        dataReceivedCallback(macAddr, data, len);
    }
}

void EspNowManager::handleDataSent(const uint8_t *macAddr, esp_now_send_status_t status) {
    if (dataSentCallback) {
        dataSentCallback(macAddr, status);
    }
}
