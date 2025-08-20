
namespace finengine {

    class FinState {
        public:
            virtual void init() = 0;
            virtual void update() = 0;
            virtual void render() = 0;
            virtual void cleanup() = 0;
    };

}
