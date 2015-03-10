#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>


#define kVel 140
#define lateral 3

int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
    //Cargo la imagen donde reside la textura del sprite
    /*sf::Texture tex;
    if (!tex.loadFromFile("resources/46118.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }*/
    sf::Texture tex2;
    if (!tex2.loadFromFile("resources/fuego.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    //sf::Sprite sprite(tex);
    
    sf::Sprite fuego(tex2);
    
    //Cojo el sprite que me interesa por defecto del sheet
    //sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
    
    fuego.setTextureRect(sf::IntRect(0, 0, 25, 25));
    
    //sprite.setOrigin(20/2,20/2);
    
    fuego.setOrigin(20/2,20/2);
    
    //sprite.setPosition(320, 240);
    
    fuego.setPosition(320, 240);
       
    sf::Clock clock;
   
    float tiempo;
    
    bool start=false;
    
    sf::Vector2i position;
    sf::Vector2f curva;
    
    float   ax, bx, cx;
    float   ay, by, cy;
    float   tSquared, tCubed;
        
    
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                //Verifico si se pulsa alguna tecla de movimiento
                switch(event.key.code) {
                        
                    //Mapeo del cursor
                    case sf::Keyboard::Right:
                    break;

                    case sf::Keyboard::Left:
                    break;
                    
                    case sf::Keyboard::Up:
                    break;

                    case sf::Keyboard::Down:
                    break;
                    
                    //Tecla ESC para salir
                    case sf::Keyboard::Escape:
                        window.close();
                    break;

                    //Cualquier tecla desconocida se imprime por pantalla su código
                    default:
                        std::cout << event.key.code << std::endl;
                    break;
                }      
            }
            
            //activa el evento cuando se presiona el botón iquierdo del ratón
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        //se recoge la posición del cursor del ratón en la pantalla qu se ha realizado
                        position = sf::Mouse::getPosition(window);
                        start=true;
                        clock.restart();
                    }
        }
        

        if(start){
           sf::Time trs = clock.getElapsedTime();
            if(trs.asMilliseconds()%10 == 0){
                int pos_cursor_x=position.x;
                int pos_cursor_y=position.y;
                int i=320;
                int y= (((i - 320)*(pos_cursor_y-240))/(pos_cursor_x-320))+240;
                fuego.setPosition(i, y);
                if(i==pos_cursor_x)
                    start=false;
            }
        }
        /*if(start){
            sf::Time trs = clock.getElapsedTime();
            if(trs.asMilliseconds()%10 == 0){
            
            int pos_cursor_x=position.x;
            int pos_cursor_y=position.y;
            sf::Vector2f p1, p2;

            //condiciones para verificar la posición del cursor y poder lanzar el bumeran
            if(pos_cursor_y > 240){
                if(pos_cursor_y < 300){
                    if(pos_cursor_x > 360){
                        if(pos_cursor_x < 420){
                            p1.x=pos_cursor_x+75;
                            p1.y=pos_cursor_y-75;
                            p2.x=pos_cursor_x-75;
                            p2.y=pos_cursor_y+75;
                        }else{
                            p1.x=pos_cursor_x+50;
                            p1.y=pos_cursor_y-100;
                            p2.x=pos_cursor_x+50;
                            p2.y=pos_cursor_y+100;
                        }
                    }else{
                        if(pos_cursor_x > 300){
                            p1.x=pos_cursor_x-75;
                            p1.y=pos_cursor_y-75;
                            p2.x=pos_cursor_x+75;
                            p2.y=pos_cursor_y+75;

                        }else{
                            p1.x=pos_cursor_x-50;
                            p1.y=pos_cursor_y-100;
                            p2.x=pos_cursor_x-50;
                            p2.y=pos_cursor_y+100;
                        }
                    }
                }else{
                    p1.x=pos_cursor_x-100;
                    p1.y=pos_cursor_y+50;
                    p2.x=pos_cursor_x+100;
                    p2.y=pos_cursor_y+50;    
                }
            }else{
                if(pos_cursor_y > 180){
                    if(pos_cursor_x > 360){
                        if(pos_cursor_x < 420){
                            p1.x=pos_cursor_x-75;
                            p1.y=pos_cursor_y-75;
                            p2.x=pos_cursor_x+75;
                            p2.y=pos_cursor_y+75;
                        }else{
                            p1.x=pos_cursor_x+50;
                            p1.y=pos_cursor_y-100;
                            p2.x=pos_cursor_x+50;
                            p2.y=pos_cursor_y+100;
                        }
                    }else{
                        if(pos_cursor_x > 300){
                            p1.x=pos_cursor_x+75;
                            p1.y=pos_cursor_y-75;
                            p2.x=pos_cursor_x-75;
                            p2.y=pos_cursor_y+75;

                        }else{
                            p1.x=pos_cursor_x-50;
                            p1.y=pos_cursor_y-100;
                            p2.x=pos_cursor_x-50;
                            p2.y=pos_cursor_y+100;
                        }
                    }
                }else{
                    p1.x=pos_cursor_x-100;
                    p1.y=pos_cursor_y-50;
                    p2.x=pos_cursor_x+100;
                    p2.y=pos_cursor_y-50;    
                }
            }
            
            //código que traza la trayectoria del bumeran (curva de Bezier)
            cx=3*(p1.x - 320);
            bx=3*(p2.x-p1.x)-cx;
            ax=320-320-cx-bx;

            cy=3*(p1.y - 240);
            by=3*(p2.y-p1.y)-cy;
            ay=240-240-cy-by;
            
            tSquared = tiempo * tiempo;
            tCubed = tSquared * tiempo;
            
            curva.x= (ax * tCubed) + (bx * tSquared) + (cx * tiempo) + 320;
            curva.y=(ay * tCubed) + (by * tSquared) + (cy * tiempo) + 240;
            
            std::cout << "x: "<< curva.x << std::endl;
            std::cout << "y: " << curva.y << std::endl;
            std::cout << "tiempo: " << tiempo << std::endl;
            
            sprite.setPosition(curva.x,curva.y);
            sprite.rotate(15);
            
            //tiempo de vuelo del bumeran
            if(tiempo>1.00){
                start=false;
                tiempo=0;
            }
            tiempo+=0.003;
            }
        }*/
    window.clear();
    window.draw(fuego);
    window.display();
    }
    return 0;
}