#include "../Headers/Settings.h"

void Settings::init() {
    primary = sf::Color(166, 166, 166);
    secondary = sf::Color::White;
    outlineSize = 2;

    fullscreen.setFont(resources.assets->getFont(Fonts::arial));
    if (resources.isFullscreen) {
        fullscreen.setString("Tela Cheia: Sim");
    } else {
        fullscreen.setString("Tela Cheia: Nao");
    }
    fullscreen.setFillColor(primary);
    fullscreen.setOutlineThickness(outlineSize);
    fullscreen.setOutlineColor(secondary);

    heroType.setFont(resources.assets->getFont(Fonts::arial));
    switch (resources.heroType) {
        case Heroes::mage:
            heroType.setString("Heroi: mago");
            break;
        case Heroes::ranger:
            heroType.setString("Heroi: arqueiro");
            break;
        case Heroes::bard:
            heroType.setString("Heroi: bardo");
            break;
    }
    heroType.setFillColor(primary);
    heroType.setOutlineThickness(outlineSize);
    heroType.setOutlineColor(secondary);

    difficulty.setFont(resources.assets->getFont(Fonts::arial));
    switch (resources.difficult) {
        case Difficulties::easy:
            difficulty.setString("Dificuldade: facil");
            break;

        case Difficulties::normal:
            difficulty.setString("Dificuldade: normal");
            break;
        case Difficulties::hard:
            difficulty.setString("Dificuldade: dificil");
            break;
    }
    difficulty.setFillColor(primary);
    difficulty.setOutlineThickness(outlineSize);
    difficulty.setOutlineColor(secondary);

    back.setFont(resources.assets->getFont(Fonts::arial));
    back.setString("Voltar");
    back.setFillColor(primary);
    back.setOutlineThickness(outlineSize);
    back.setOutlineColor(secondary);

    resize();
}

void Settings::handleEvents(sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (fullscreen.getGlobalBounds().contains(
                        static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                    if (resources.isFullscreen) {
                        fullscreen.setString("Tela Cheia: nao");
                        resources.window->close();
                        resources.window->create(sf::VideoMode(1280, 720), "Base Defense", sf::Style::Default);
                    } else {
                        fullscreen.setString("Tela Cheia: sim");
                        resources.window->close();
                        resources.window->create(sf::VideoMode::getDesktopMode(), "Base Defense",
                                                 sf::Style::Fullscreen);
                    }
                    resources.isFullscreen = !resources.isFullscreen;
                    resize();
                }
                if (heroType.getGlobalBounds().contains(
                        static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                    switch (resources.heroType) {
                        case Heroes::mage:
                            heroType.setString("Heroi: arqueiro");
                            resources.heroType = Heroes::ranger;
                            break;
                        case Heroes::ranger:
                            heroType.setString("Heroi: bardo");
                            resources.heroType = Heroes::bard;
                            break;
                        case Heroes::bard:
                            heroType.setString("Heroi: mago");
                            resources.heroType = Heroes::mage;
                            break;
                    }
                }
                if (difficulty.getGlobalBounds().contains(
                        static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                    switch (resources.difficult) {
                        case Difficulties::easy:
                            difficulty.setString("Dificuldade: normal");
                            resources.difficult = Difficulties::normal;
                            break;
                        case Difficulties::normal:
                            difficulty.setString("Dificuldade: dificil");
                            resources.difficult = Difficulties::hard;
                            break;
                        case Difficulties::hard:
                            difficulty.setString("Dificuldade: facil");
                            resources.difficult = Difficulties::easy;
                            break;
                    }
                    resize();
                }

                if (back.getGlobalBounds().contains(
                        static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
                    next = StateType::Menu;
                }
            }
    }
}

void Settings::update(float dt) {
    if (back.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        fullscreen.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        heroType.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window))) ||
        difficulty.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*resources.window)))) {
        resources.window->setMouseCursor(resources.assets->getCursor(Cursors::hand));
    } else {
        resources.window->setMouseCursor(sf::Cursor());
    }
}

void Settings::render() {
    resources.window->clear();
    resources.window->draw(fullscreen);
    resources.window->draw(heroType);
    resources.window->draw(difficulty);
    resources.window->draw(back);
    resources.window->display();
}

void Settings::resize() {
    float width = resources.window->getSize().x;
    float heigth = resources.window->getSize().y;

    fullscreen.setCharacterSize(heigth / 14);
    fullscreen.setPosition((width - fullscreen.getGlobalBounds().width) / 2,
                           (heigth - fullscreen.getGlobalBounds().height) / 3);

    heroType.setCharacterSize(heigth / 14);
    heroType.setPosition((width - heroType.getGlobalBounds().width) / 2,
                         (heigth - heroType.getGlobalBounds().height) / 2.2);

    difficulty.setCharacterSize(heigth / 14);
    difficulty.setPosition((width - difficulty.getGlobalBounds().width) / 2,
                           (heigth - difficulty.getGlobalBounds().height) / 1.8);

    back.setCharacterSize(heigth / 14);
    back.setPosition((width - back.getGlobalBounds().width) / 2, (heigth - back.getGlobalBounds().height) / 1.1);
}