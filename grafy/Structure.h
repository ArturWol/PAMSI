
#pragma once

//STWORZONE STRUKTURY POMAGAJACE W DZIALANIU PROGRAMU

struct dane {
	int dystans;
	bool odwiedzony;
};

struct Element {
	Element * nastepny;
	int wezel;
	int waga;
};

