#ifndef IGAMESCREEN_H
#define IGAMESCREEN_H


class iGameScreen
{
    enum class screenState{
        NONE,
        RUNNING,
        EXIT,
        CHANGE_NEXT,
        CHANGE_PREV
    };
    public:
        iGameScreen();
        virtual ~iGameScreen();
        virtual void build() = 0;
        virtual void destroy() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
		screenState getState()const {};
    protected:

        int m_index = -1;
        screenState m_currentState = screenState::NONE;
        //iGame* m_game = nullptr;
    private:
};

#endif // IGAMESCREEN_H
