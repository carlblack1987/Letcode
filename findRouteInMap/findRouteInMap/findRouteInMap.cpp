// findRouteInMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>

using namespace std;

struct Point{
	int x;
	int y;
	bool operator == (const Point b);
	Point& operator = (const Point &b);
	//Point& operator + (const Point &b);
};

bool Point::operator == (Point b) {
	if (this->x == b.x && this->y == b.y)
		return true;
	else
		return false;
}

Point& Point::operator = (const Point &b) {
	this->x = b.x;
	this->y = b.y;
	return *this;
}

//Point& Point::operator + (const Point &b) {
//	this->x += b.x;
//	this->y += b.y;
//	return *this;
//}

Point operator + (const Point a, const Point b) {
	Point temp;
	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	return temp;
	/*this->x += b.x;
	this->y += b.y;
	return *this;*/
}

Point movement[4] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

void displayMap(char a[][8], int row, int col) {
	cout << "*******************" << endl;
	cout << "This is the result:" << endl;
	cout << "*******************" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
}

void getStartEndPoint(char a[][8], int row, int col, Point &startP, Point &endP) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (a[i][j] == 'S') {
				startP.x = i;
				startP.y = j;
			}
			if (a[i][j] == 'G') {
				endP.x = i;
				endP.y = j;
			}
		}
	}
}

bool findRouteInMap(char map1[][8], Point startP, Point endP, int visit[][8], Point **&prePoints) {
	Point cur = startP;
	if (startP == endP)
		return true;
	queue<Point>que;
	que.push(cur);
	visit[cur.x][cur.y] = 1;

	while (!que.empty()) {
		cur = que.front();
		que.pop();
		cout << "Current: " << cur.x << " " << cur.y << endl;
		for (int i = 0; i < 4; i++) {
			Point temp = cur + movement[i];
			//cout << "Temp: " << temp.x << " " << temp.y << endl;
			if (temp.x >= 0 && temp.x < 10 && temp.y >= 0 && temp.y < 8) {
				if (temp == endP) {
					visit[temp.x][temp.y] = 1;
					prePoints[endP.x][endP.y] = cur;
					return true;
				}
				else if (0 == visit[temp.x][temp.y] && map1[temp.x][temp.y] != '#') {
					que.push(temp);
					visit[temp.x][temp.y] = 1;
					prePoints[temp.x][temp.y] = cur;
				}
			}
		}
	}
	return false;
}

void printResult(char map1[][8], Point **&prePoints, Point startP, Point endP) {
	Point cur = prePoints[endP.x][endP.y];
	while (!(cur == startP)) {
		cout << "Current2: " << cur.x << " " << cur.y << endl;
		map1[cur.x][cur.y] = '@';
		cur = prePoints[cur.x][cur.y];
	}

	displayMap(map1, 10, 8);
}

int _tmain(int argc, _TCHAR* argv[])
{
	char map1[10][8] = {
		{ '+', 'G', '+', '+', '+', '+', '+', '+', },
		{ '+', '+', '+', '+', '+', '+', '+', '+', },
		{ '+', '+', '+', '+', '+', '+', '+', '+', },
		{ '+', '+', '+', '+', '+', '+', '+', '+', },
		{ '+', '+', '+', '+', '+', '+', '+', '+', },
		{ '#', '#', '#', '#', '#', '#', '#', '+', },
		{ '#', '+', '+', '+', '+', '+', '+', '+', },
		{ '#', '+', '+', '+', '+', '+', '+', '+', },
		{ '#', 'S', '+', '+', '+', '+', '+', '+', },
		{ '#', '#', '#', '#', '#', '#', '+', '+', },
	};
	Point startP, endP;
	Point **prePoints;
	prePoints = new Point*[10];
	for (int i = 0; i < 10; i++)
		prePoints[i] = new Point[8];
	int visit[10][8] = { 0 };
	
	getStartEndPoint(map1, 10, 8, startP, endP);
	if (findRouteInMap(map1, startP, endP, visit, prePoints)) {
		cout << "Destination has been found." << endl;
		printResult(map1, prePoints, startP, endP);
	}
	else
		cout << "Could not find a route to the destination." << endl;

	/*Point a, b, c;
	a.x = 1, a.y = 1, b.x = 1, b.y = 1;
	c = a + b;
	cout << a.x << " " << a.y << endl;
	cout << b.x << " " << b.y << endl;
	cout << c.x << " " << c.y << endl;*/

	getchar();
	return 0;
}

