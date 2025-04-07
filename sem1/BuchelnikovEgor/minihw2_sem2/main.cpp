#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <ctime>

// (V) 1. M x N двумерное поле с тайлами(в примере 10 x 10)
// (V) 2. Скрытые тайлы -> открытые с эвентами
// (X) 3. эвенты должны отображаться, + Логика
// (X) 4. Под каждым тайлом с вероятность в 10% есть консервы,
// при вскрытии тайла -> восст. сытость
// (V) 5. Открыть M x N тайлов (все тайлы) для победы
// (V) 6. Экран победы + экран поражения
// (V) 7. За каждое открытие тайла теряем 1 сытость. Сытость равно 0,
// тогда поражение, + отображать сытость
// (V) 8. Начальное значени сытости - 25

#define CELLSIZE_M 10
#define CELLSIZE_N 10
#define CHANCE_FOOD 10
#define CHANCE_MONSTER 15

#define ENERGY_MAX 100
#define HP_MAX 5

#define CELLSIZE_SCREEN 100.f

enum CellType {
    Type_Grass,
    Type_Hill,
    Type_Forest,
    Type_Stone,
    Type_Sand,
    Type_Snow,
    Type_Water,
    Type_End
};
enum TextureType {
    Texture_Grass,
    Texture_Hill,
    Texture_Forest,
    Texture_Stone,
    Texture_Sand,
    Texture_Snow,
    Texture_Water,
    Texture_Hide,
    Texture_Soup,
    Texture_Monster,
    Texture_End };

struct Cell {
    bool isHidden;
    bool isFood;
    bool isMonster;
    CellType cellType;
};

bool isWinOfGame(const Cell cells[CELLSIZE_M][CELLSIZE_N], const int& hp) {
    bool winCondition = true;
    for (int x = 0; x < CELLSIZE_M; x++) {
        for (int y = 0; y < CELLSIZE_N; y++) {
            if (cells[x][y].isHidden) {
                winCondition = false;
                break;
            }
        }
    }
    return winCondition && hp > 0;
}

bool isLoseOfGame(const int& energy, const int& hp) {
    return energy <= 0 || hp <= 0;
}

void clickTile(sf::RenderWindow& window, Cell cells[CELLSIZE_M][CELLSIZE_N], int& energy, int& hp, sf::RectangleShape shapes[CELLSIZE_M][CELLSIZE_N], sf::Texture textures[TextureType::Texture_End]) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    const int x = mousePos.x / CELLSIZE_SCREEN;
    const int y = mousePos.y / CELLSIZE_SCREEN;

    if (cells[x][y].isHidden) {
        cells[x][y].isHidden = false;
        if (cells[x][y].isFood) {
            energy = ENERGY_MAX;
            hp = std::min(hp + 1, HP_MAX);
            shapes[x][y].setTexture(&textures[TextureType::Texture_Soup]);
        }
        else if (cells[x][y].isMonster) {
            hp--;
            shapes[x][y].setTexture(&textures[TextureType::Texture_Monster]);
        }
        else {
            shapes[x][y].setTexture(&textures[cells[x][y].cellType]);
        }
    }
}

int main() {
    int energy = ENERGY_MAX;
    int hp = HP_MAX;

    // Инициализация случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    Cell cells[CELLSIZE_M][CELLSIZE_N];
    for (int x = 0; x < CELLSIZE_M; x++) {
        for (int y = 0; y < CELLSIZE_N; y++) {
            cells[x][y].isHidden = true;
            cells[x][y].isFood = rand() % 100 < CHANCE_FOOD;
            cells[x][y].isMonster = !cells[x][y].isFood && (rand() % 100 < CHANCE_MONSTER);
            cells[x][y].cellType = static_cast<CellType>
                (rand() % (CellType::Type_End - 1));
        }
    }


    sf::RenderWindow window(sf::VideoMode(
        static_cast<unsigned int>(CELLSIZE_SCREEN * CELLSIZE_M),
        static_cast<unsigned int>(CELLSIZE_SCREEN * CELLSIZE_N)),
        "NOT MINESWEEPER GAME", sf::Style::Default);

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("../../resources/Arial.ttf")) {
        return -1;
    }

    // Создание текста
    sf::Text textEnergy;
    textEnergy.setFont(font);
    textEnergy.setCharacterSize(24);
    textEnergy.setFillColor(sf::Color::White);
    textEnergy.setPosition(10, 10);

    sf::Text textHP;
    textHP.setFont(font);
    textHP.setCharacterSize(24);
    textHP.setFillColor(sf::Color::White);
    textHP.setPosition(10, 40);

    sf::Text textCondition;
    textCondition.setFont(font);
    textCondition.setCharacterSize(24);
    textCondition.setFillColor(sf::Color::White);
    textCondition.setPosition(static_cast<float>(CELLSIZE_SCREEN * CELLSIZE_M) / 2 - 100, 10);

    sf::RectangleShape shapes[CELLSIZE_M][CELLSIZE_N];
    sf::Texture textures[TextureType::Texture_End];
    if (!textures[TextureType::Texture_Grass].loadFromFile("../../resources/grass.png") ||
        !textures[TextureType::Texture_Hill].loadFromFile("../../resources/hill.png") ||
        !textures[TextureType::Texture_Forest].loadFromFile("../../resources/forest.png") ||
        !textures[TextureType::Texture_Stone].loadFromFile("../../resources/stone.png") ||
        !textures[TextureType::Texture_Sand].loadFromFile("../../resources/sand.png") ||
        !textures[TextureType::Texture_Snow].loadFromFile("../../resources/snow.png") ||
        !textures[TextureType::Texture_Water].loadFromFile("../../resources/water.png") ||
        !textures[TextureType::Texture_Hide].loadFromFile("../../resources/hide.png") ||
        !textures[TextureType::Texture_Soup].loadFromFile("../../resources/soup.png") ||
        !textures[TextureType::Texture_Monster].loadFromFile("../../resources/monster.png")) {
        return -1;
    }

    for (int x = 0; x < CELLSIZE_M; x++) {
        for (int y = 0; y < CELLSIZE_N; y++) {
            
            // TODO функцию а не напрямую
            if (cells[x][y].isHidden)
                shapes[x][y].setTexture(&textures[TextureType::Texture_Hide]);
            else
                shapes[x][y].setTexture(&textures[cells[x][y].cellType]); 

            shapes[x][y].setPosition(
                sf::Vector2f(x * CELLSIZE_SCREEN, y * CELLSIZE_SCREEN));
            shapes[x][y].setSize({ CELLSIZE_SCREEN, CELLSIZE_SCREEN });
        }
    }

    bool mousepressed = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                mousepressed = false;
            }

            if (!mousepressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                mousepressed = true;
                clickTile(window, cells, energy, hp, shapes, textures);
                energy--;
                textEnergy.setString("Energy: " + std::to_string(energy));
                textHP.setString("HP: " + std::to_string(hp) + "/" + std::to_string(HP_MAX));

                if (isWinOfGame(cells, hp))
                    textCondition.setString("WINNER!!!");
                if (isLoseOfGame(energy, hp))
                    textCondition.setString("LOSER!!!");
            }
        }

        window.clear();
        for (int x = 0; x < CELLSIZE_M; x++) {
            for (int y = 0; y < CELLSIZE_N; y++) {
                window.draw(shapes[x][y]);
            }
        }
        window.draw(textEnergy);
        window.draw(textHP);
        window.draw(textCondition);
        window.display();
    }
}