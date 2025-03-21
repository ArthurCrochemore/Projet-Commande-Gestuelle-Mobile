#include <cstdint>

class IdentifyActionFactory {
public:
    static const uint8_t VOLUME = 1;
    static const uint8_t BRIGHTNESS = 2;

    static IServiceIdentifyAction* createAction(int actionType) {
        switch (actionType) {
            case VOLUME: return new ServiceIdentifyActionVolume();
            case BRIGHTNESS: return new ServiceIdentifyActionBrightness();
            default: return nullptr;
        }
    }
};

class IServiceIdentifyAction {
    public:
        virtual uint8_t identify(const QImage& image) = 0;
        virtual ~IServiceIdentifyAction() = default;
    };
    
    class ServiceIdentifyActionVolume : public IServiceIdentifyAction {
    public:
        uint8_t identify(const QImage& image) override {
            // TODO : Implémentation de l'identification d'une action lié au volume
        }
    };
    
    class ServiceIdentifyActionBrightness : public IServiceIdentifyAction {
    public:
        uint8_t identify(const QImage& image) override {
            // TODO : Implémentation de l'identification d'une action lié à la luminosité
        }
    };
    