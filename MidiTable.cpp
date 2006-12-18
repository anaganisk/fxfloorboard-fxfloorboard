/**************************************************************************** 
** 
** Copyright (C) 2005-2006 Uco Mesdag. All rights reserved. 
** 
** This file is part of "GT-8 FX FloorBoard". 
** 
** This program is free software; you can redistribute it and/or modify 
** it under the terms of the GNU General Public License as published by 
** the Free Software Foundation; either version 2 of the License, or 
** (at your option) any later version. 
** 
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of 
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
** GNU General Public License for more details. 
** 
** You should have received a copy of the GNU General Public License along 
** with this program; if not, write to the Free Software Foundation, Inc., 
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. 
** 
****************************************************************************/ 
 
#include "MidiTable.h"     
#include "MidiTableDestroyer.h" 
#include <QFile> 
 
MidiTable::MidiTable()  
{ 
    loadMidiMap(); 
}; 
 
MidiTable* MidiTable::_instance = 0;// initialize pointer 
MidiTableDestroyer MidiTable::_destroyer; 
 
MidiTable* MidiTable::Instance()  
{ 
    /* Multi-threading safe */ 
    if (!_instance /*_instance == 0*/)  // is it the first call? 
    {   
        _instance = new MidiTable; // create sole instance 
        _destroyer.SetMidiTable(_instance); 
    }; 
    return _instance; // address of sole instance 
 
    /* Single-threading */ 
    /* 
    static Preferences inst; 
    return &inst; 
    */ 
}; 
 
void MidiTable::loadMidiMap() 
{ 
    QDomDocument doc( "MIDI Transalation" ); 
    QFile file( "midi.xml" ); 
    doc.setContent( &file );                    // file is a QFile 
    file.close(); 
    QDomElement root = doc.documentElement();   // Points to <SysX> 
    this->root = root; 
 
    //QVector<Midi> midiMap; 
     
    QDomNode node = root.firstChild(); 
    while ( !node.isNull() )  
    { 
        Midi section; 
		section.type.append(node.nodeName()); 
		
		QDomNode level1Node = node.firstChild(); 
        while ( !level1Node.isNull() )  
        { 
            Midi level1; 
			level1.type.append(level1Node.nodeName()); 
            level1.name = level1Node.attributes().namedItem("name").nodeValue(); 
            level1.value = level1Node.attributes().namedItem("value").nodeValue();             
            level1.abbr = level1Node.attributes().namedItem("abbr").nodeValue(); 
            level1.desc = level1Node.attributes().namedItem("desc").nodeValue(); 
         
            QDomNode level2Node = level1Node.firstChild(); 

            while ( !level2Node.isNull() )  
            { 
                Midi level2; 
				level2.type.append(level2Node.nodeName());
				level2.name = level2Node.attributes().namedItem("name").nodeValue(); 
				level2.value = level2Node.attributes().namedItem("value").nodeValue();             
				level2.abbr = level2Node.attributes().namedItem("abbr").nodeValue(); 
				level2.desc = level2Node.attributes().namedItem("desc").nodeValue(); 

				QDomNode level3Node = level2Node.firstChild(); 
                
                while ( !level3Node.isNull() )  
                { 	
					Midi level3; 
					level3.type.append(level3Node.nodeName());
					level3.name = level3Node.attributes().namedItem("name").nodeValue(); 
					level3.value = level3Node.attributes().namedItem("value").nodeValue();             
					level3.abbr = level3Node.attributes().namedItem("abbr").nodeValue(); 
					level3.desc = level3Node.attributes().namedItem("desc").nodeValue(); 

					QDomNode  level4Node = level3Node.firstChild();
                    
                    while ( !level4Node.isNull() )  
                    { 
						Midi level4; 
						level4.type.append(level4Node.nodeName());
						level4.name = level4Node.attributes().namedItem("name").nodeValue(); 
						level4.value = level4Node.attributes().namedItem("value").nodeValue();             
						level4.abbr = level4Node.attributes().namedItem("abbr").nodeValue(); 
						level4.desc = level4Node.attributes().namedItem("desc").nodeValue(); 
	 
						QDomNode level5Node = level4Node.firstChild();

						while ( !level5Node.isNull() )  
						{ 
							Midi level5; 
							level5.type.append(level5Node.nodeName());
							level5.name = level5Node.attributes().namedItem("name").nodeValue(); 
							level5.value = level5Node.attributes().namedItem("value").nodeValue();             
							level5.desc = level5Node.attributes().namedItem("desc").nodeValue();

							level4.id.append(level5.value); 
							level4.level.append(level5); 
							level5Node = level5Node.nextSibling(); 
						}; 

						level3.id.append(level4.value);
						level3.level.append(level4); 
						level4Node = level4Node.nextSibling();
                    }; 

					level2.id.append(level3.value);
                    level2.level.append(level3); 
                    level3Node = level3Node.nextSibling(); 
                }; 
				
				level1.id.append(level2.value);
                level1.level.append(level2);  
                level2Node = level2Node.nextSibling(); 
            }; 

			section.id.append(level1.value);
			section.level.append(level1); 
            level1Node = level1Node.nextSibling(); 
        }; 

		QString test = node.nodeName();
		this->midiMap.id.append(test); 
		this->midiMap.level.append(section); 
        node = node.nextSibling(); 
    }; 
}; 

Midi MidiTable::getMidiMap(QString root, QString hex1)
{ 
	Midi section = midiMap.level.at( midiMap.id.indexOf(root) );
	Midi level1 = section.level.at( section.id.indexOf(hex1) );;
	return level1; 
};

Midi MidiTable::getMidiMap(QString root, QString hex1, QString hex2)
{ 
	Midi section = midiMap.level.at( midiMap.id.indexOf(root) );
	Midi level1 = section.level.at( section.id.indexOf(hex1) );
	Midi level2 = level1.level.at( level1.id.indexOf(hex2) );
	return level2; 
};

Midi MidiTable::getMidiMap(QString root, QString hex1, QString hex2, QString hex3)
{ 
	Midi section = midiMap.level.at( midiMap.id.indexOf(root) );
	Midi level1 = section.level.at( section.id.indexOf(hex1) );
	Midi level2 = level1.level.at( level1.id.indexOf(hex2) );
	Midi level3 = level2.level.at( level2.id.indexOf(hex3) );
	return level3; 
};

Midi MidiTable::getMidiMap(QString root, QString hex1, QString hex2, QString hex3,  QString hex4)
{ 
	Midi section = midiMap.level.at( midiMap.id.indexOf(root) );
	Midi level1 = section.level.at( section.id.indexOf(hex1) );
	Midi level2 = level1.level.at( level1.id.indexOf(hex2) );
	Midi level3;
	if(!level2.id.contains(hex3) && level2.id.contains("range"))
	{
		level3 = level2.level.at( level2.id.indexOf("range") );
	}
	else
	{
		level3 = level2.level.at( level2.id.indexOf(hex3) );
	};

	Midi level4 = level3.level.at( level3.id.indexOf(hex4) );
	return level4; 
};

Midi MidiTable::getMidiMap(QString root, QString hex1, QString hex2, QString hex3,  QString hex4, QString hex5)
{ 
	Midi section = midiMap.level.at( midiMap.id.indexOf(root) );
	Midi level1 = section.level.at( section.id.indexOf(hex1) );
	Midi level2 = level1.level.at( level1.id.indexOf(hex2) );
	Midi level3 = level2.level.at( level2.id.indexOf(hex3) );
	Midi level4 = level3.level.at( level3.id.indexOf(hex4) );
	Midi level5 = level4.level.at( level4.id.indexOf(hex5) );
	return level5; 
};