#pragma once

#include <esp_now.h>
#include <WiFi.h>

class EspNowManager {
public:
    // Typ dla callbacków
    typedef void (*OnDataReceivedCallback)(const uint8_t *macAddr, const uint8_t *data, int len);
    typedef void (*OnDataSentCallback)(const uint8_t *macAddr, esp_now_send_status_t status);

    // Konstruktor
    EspNowManager();

    // Inicjalizacja ESP-NOW
    bool begin();

    // Rejestracja callbacków
    void onReceive(OnDataReceivedCallback callback);
    void onSend(OnDataSentCallback callback);

    // Dodanie urządzenia docelowego
    bool addPeer(const uint8_t *peerAddress);

    // Wysłanie danych
    bool sendData(const uint8_t *peerAddress, const uint8_t *data, size_t len);

private:
    static OnDataReceivedCallback dataReceivedCallback;
    static OnDataSentCallback dataSentCallback;

    // Statyczne metody callbacków
    static void handleDataReceived(const uint8_t *macAddr, const uint8_t *data, int len);
    static void handleDataSent(const uint8_t *macAddr, esp_now_send_status_t status);
};
