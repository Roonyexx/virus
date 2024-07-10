#include "Simulation.h"
#include <iostream>



Simulation::Simulation(float mortality, float infProb, uint32_t incTime, uint32_t infDur, uint32_t walkRange, uint32_t hospitalCapacity, uint32_t maskPercent, uint32_t contactsPerDay)
    : population{ sf::Vector2u(1120, 720), walkRange, &hospital, maskPercent }, virus{ mortality, infProb, incTime, infDur }, 
    window{ sf::VideoMode{ 1280, 720 }, "Virus", sf::Style::Titlebar | sf::Style::Close }, walkRange{ walkRange },
    hospital{ hospitalCapacity }, maskPercent{ maskPercent }, contactsPerDay{ contactsPerDay }
{
    gui.setWindow(window);
}

void Simulation::step()
{
    population.update(virus, contactsPerDay);
}

void Simulation::reset()
{
    Field newPopulation{ sf::Vector2u(1120, 720), walkRange, &hospital, maskPercent };
    population = newPopulation;
    paused = true;
}


void Simulation::run()
{
    initializeUI();
    while (window.isOpen()) 
    {
        handleEvents();
        if(!paused) population.update(virus, contactsPerDay);
        window.clear({ 30, 30, 30 });
        population.draw(window);
        gui.draw();
        window.display();
    }
}

void Simulation::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        gui.handleEvent(event);

        if (event.type == sf::Event::Closed) 
        {
            window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
                sf::Vector2i pos{ sf::Mouse::getPosition(window) };
                Person* p{ population.findPerson(pos) };
                if (p != nullptr && p->getStatus() == Status::Healthy)
                {
                    p->setStatus(Status::incubationPeriod);
                }
        }
    }
}

void Simulation::initializeUI()
{
    using namespace tgui;
    auto mainGroup = Group::create();
    mainGroup->setPosition(1120, 0);
    mainGroup->setSize(160, 720);
    

    auto createSliderWithLabel = 
        [](auto onValueChanged, const String& label, const sf::Vector2f position, const float min = 0, const float max = 10, const float startValue = 0.f, const float step = 0.1f, const uint32_t decimalPlaces = 0) {
        auto subGroup = Group::create();
        subGroup->setPosition(position.x, position.y);

        auto labelWidget = Label::create(label);
        labelWidget->setPosition(0, 0);
        labelWidget->setHorizontalAlignment(HorizontalAlignment::Center);
        labelWidget->setVerticalAlignment(VerticalAlignment::Bottom);
        labelWidget->setTextSize(10);
        labelWidget->getRenderer()->setTextColor(sf::Color::White);
        labelWidget->getRenderer()->setTextStyle(TextStyle::Bold);


        auto slider = EditBoxSlider::create(min, max, startValue, decimalPlaces, step);
        slider->setValue(startValue);
        slider->setPosition(5, 20);
        slider->onValueChange(onValueChanged);

        labelWidget->setSize(slider->getSize().x, 20);

        subGroup->add(labelWidget);
        subGroup->add(slider);

        return subGroup;
    };

    auto createButton = [](auto battonPressed, const String& label, const sf::Vector2f position) {
        auto button = Button::create(label);
        button->onClick(battonPressed);
        button->setPosition(position.x, position.y);

        button->setSize(45, 40);
        return button;
    };

    auto reset = createButton([this]() { this->reset(); }, "reset", { 7, 10 });
    auto start = createButton([this]() { this->paused = !(this->paused); }, "start", { 57, 10 });
    auto step = createButton([this]() { this->step(); }, "step", { 107, 10 });

    mainGroup->add(reset);
    mainGroup->add(start);
    mainGroup->add(step);

    auto mortality = createSliderWithLabel([virus = &virus](float value){ virus->setMortality(value); }, "mortality", { 0, 50 }, 0, 1, virus.getMortality(), 0.01f, 2);
    auto infProb = createSliderWithLabel([virus = &virus](float value){ virus->setInfectionProbability(value); }, "infection probability", { 0, 100 }, 0, 1, virus.getInfectionProbability(), 0.01f, 2);
    auto incTime = createSliderWithLabel([virus = &virus](float value){ virus->setIncubationTime(round(value)); }, "incubation time", { 0, 150 }, 0, 50, virus.getIncubationTime(), 0);
    auto infDur = createSliderWithLabel([virus = &virus](float value){ virus->setInfectionDuration(round(value)); }, "infection duration", { 0, 200 }, 1, 50, virus.getInfectionDuration(), 0);
    auto walkRange = createSliderWithLabel([this, population = &population](float value){ this->walkRange = round(value); population->setWalkRange(this->walkRange); }, "walk range", { 0, 250 }, 0, 50, this->walkRange, 0);
    auto hospitalCapacity = createSliderWithLabel([hospital = &hospital, population = &population](float value) { 
        hospital->setCapacity(population->percentToPeople(round(value)));
    }, "hospital capacity", { 0, 300 }, 0, 100, 0, 0);
    auto maskPercent = createSliderWithLabel([this](float value) { this->maskPercent = round(value); }, "mask percent", { 0, 350 }, 0, 100, this->maskPercent, 0);
    auto contactsPerDay = createSliderWithLabel([this](float value) { this->contactsPerDay = round(value); }, "contacts per day", { 0, 400 }, 0, 100, this->contactsPerDay, 0);


    mainGroup->add(mortality);
    mainGroup->add(infProb);
    mainGroup->add(incTime);
    mainGroup->add(infDur);
    mainGroup->add(walkRange);
    mainGroup->add(hospitalCapacity);
    mainGroup->add(maskPercent);
    mainGroup->add(contactsPerDay);








    auto statusGroup = Group::create();
    statusGroup->setPosition(10, 530);
    statusGroup->setSize(160, 200);

    auto createStatusWidget = [](const String& text, const sf::Color color, const Vector2f position) {
        auto statusGroup = Group::create();
        statusGroup->setPosition(position);

        auto colorBox = Panel::create({ 20, 20 });
        colorBox->getRenderer()->setBackgroundColor(color);
        colorBox->setPosition(0, 0);

        auto label = Label::create(text);
        label->setPosition(22, 3);
        label->setTextSize(12);
        label->getRenderer()->setTextStyle(TextStyle::Bold);
        label->getRenderer()->setTextColor(sf::Color::White);

        statusGroup->add(colorBox);
        statusGroup->add(label);

        return statusGroup;
    };

    statusGroup->add(createStatusWidget("Healthy", { 238, 238, 238 }, { 0, 0 }));
    statusGroup->add(createStatusWidget("Incubation Period", { 242, 209, 213 }, { 0, 30 }));
    statusGroup->add(createStatusWidget("Infected", { 255, 0, 0 }, { 0, 60 }));
    statusGroup->add(createStatusWidget("In Hospital", { 30, 199, 85 }, { 0, 90 }));
    statusGroup->add(createStatusWidget("Recovered", { 50, 205, 209 }, { 0, 120 }));
    statusGroup->add(createStatusWidget("Dead", { 20, 1, 1 }, { 0, 150 }));

    mainGroup->add(statusGroup);

    gui.add(mainGroup);
}
