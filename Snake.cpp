#include "Snake.h"
#include "Game.h"
 #include <SDL.h>
#include <iostream>
 #include <bits/stdc++.h>

 using namespace std;

Snake::Snake(Game& _game, Position start)
    : head(new SnakeNode(start)), tail(head), game(_game), cherry(0)
{
    game.snakeMoveTo(start);
}

Snake::~Snake()
{
     SnakeNode* p = this->tail;
    while(p != NULL){
       SnakeNode* nextNode = p->next;
       delete p;
       p = nextNode;
    }
}


vector<Position> Snake::getPositions() const
{
    vector<Position> res;
    for (SnakeNode* p = tail; p != nullptr; p = p->next)
        res.push_back(p->position);
    return res;
}

void Snake::growAtFront(Position newPosition)
{

	head->next = new SnakeNode(newPosition , NULL);
	head = head->next ;

}




void Snake::slideTo(Position newPosition)
{
	if (tail->next == nullptr) {


		tail->position = newPosition ;
	}
	else {
		SnakeNode *oldTailNode = tail;


		tail = tail->next ;
		oldTailNode->next = NULL;


        oldTailNode->position = newPosition ;
        head->next = oldTailNode ;
		head = oldTailNode;
	}
}


void Snake::eatCherry()
{

	cherry ++ ;
}



void Snake::move(Direction direction)
{
    Position newPosition = head->position.move(direction);


    game.snakeMoveTo(newPosition);

    if(game.isGameOver()) return ;

    if (cherry > 0) {

        cherry -- ;
        growAtFront(newPosition);
    } else {
    	game.snakeLeave(tail->position);

        slideTo(newPosition);
    }
}


int Snake::getNumCherry(){
    return cherry;
}

int Snake::getScore()
{
    return score;
}

SnakeNode* Snake::getHead(){
    return head;
}


SnakeNode* Snake::getTail(){
    return tail;
}
