//// DrumTypeCodes.h //////////////////////////////////
//
//	These codes represent the drum types for etm files
//
///////////////////////////////////////////////////////

#pragma once
#ifndef DRUMTYPECODES_H
#define DRUMTYPECODES_H

inline wxArrayString GetDrumTypes()
{
	wxArrayString drumTypes;

	drumTypes.Add(wxT(""));              //0
	drumTypes.Add(wxT("Kick Drum"));     //1
	drumTypes.Add(wxT("Hi-Hat Pedal"));  //2
	drumTypes.Add(wxT("Hi-Hat"));        //3
	drumTypes.Add(wxT("Snare 1"));       //4
	drumTypes.Add(wxT("Snare 2"));       //5
	drumTypes.Add(wxT("Tom 1"));         //6
	drumTypes.Add(wxT("Tom 2"));         //7
	drumTypes.Add(wxT("Tom 3"));         //8
	drumTypes.Add(wxT("Tom 4"));         //9
	drumTypes.Add(wxT("Tom 5"));         //10
	drumTypes.Add(wxT("Tom 6"));         //11
	drumTypes.Add(wxT("Tom 7"));         //12
	drumTypes.Add(wxT("Tom 8"));         //13
	drumTypes.Add(wxT("Splash 1"));      //14
	drumTypes.Add(wxT("Splash 2"));      //15
	drumTypes.Add(wxT("Splash 3"));      //16
	drumTypes.Add(wxT("Splash 4"));      //17
	drumTypes.Add(wxT("Splash 5"));      //18
	drumTypes.Add(wxT("Crash 1"));       //19
	drumTypes.Add(wxT("Crash 2"));       //20
	drumTypes.Add(wxT("Crash 3"));       //21
	drumTypes.Add(wxT("Crash 4"));       //22
	drumTypes.Add(wxT("Crash 5"));       //23
	drumTypes.Add(wxT("Ride 1"));        //24
	drumTypes.Add(wxT("Ride 2"));        //25
	drumTypes.Add(wxT("China 1"));       //26
	drumTypes.Add(wxT("China 2"));       //27
	drumTypes.Add(wxT("Cow Bell 1"));    //28
	drumTypes.Add(wxT("Cow Bell 2"));    //29
	drumTypes.Add(wxT("Wood Block 1"));  //30
	drumTypes.Add(wxT("Wood Block 2"));  //31
	drumTypes.Add(wxT("Percussion 1"));  //32
	drumTypes.Add(wxT("Percussion 2"));  //33
	drumTypes.Add(wxT("Percussion 3"));  //34
	drumTypes.Add(wxT("Percussion 4"));  //35
	drumTypes.Add(wxT("Percussion 5"));  //36
	drumTypes.Add(wxT("Percussion 6"));  //37
	drumTypes.Add(wxT("Percussion 7"));  //38
	drumTypes.Add(wxT("Percussion 8"));  //39
	drumTypes.Add(wxT("Percussion 9"));  //40

	return drumTypes;
}

#endif //DRUMTYPECODES_H