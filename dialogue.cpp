#include "dialogue.h"
#include <iostream>

dialogue::dialogue() // constructor, resolution operator (scope r.o. = access members to the class)::function name
{
}

void dialogue::introdiag() { // absence of data or type  resolution operator::function name   R"( )" represents a raw string, it treats everything inside of it as a string. This is implemented here for easier dialogue. This is also used consistently!
	std::cout << R"(Press Enter to continue . . .
-------------------------------------------------------------
You: "Besides the fact that this was abandoned 3 years ago, 
there aren't any files related to this laboratory. Whoever
abandoned this place... they must've really wanted this
place to be forgotten. But going here alone? My boss really
doesn't care, he's such a bum...")" << std::endl;
	std::cin.get(); //reads a single character from the input buffer. used to force the program to wait for user to press any key to continue
	std::cout << R"(-------------------------------------------------------------
You: "Whatever... But what could this lab possibly contain, 
to the point where NO ONE dares to step close? It's too 
suspicious.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
*As you entered the main lab, the eerie atmosphere sent 
chills down your spine, asbestos filling the air like 
snowflakes, making breathing ever so slightly difficult.*)" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
*Streaks of light poured in from small crevices in the walls, 
giving a little bit of salvation for visibility.*)" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "It's so dark in here...")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 1: "Stop right there! I know what your 
intentions are!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Who's there!" *You clutch your pistol.*)" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 1: "Funny, I was about to ask you the same 
thing.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Show yourself! Now." *You raise your pistol but someone 
jumps forward and snatches your pistol.*)" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 1: "Interesting toy... Now get out!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Calm down! Let's not be rash here... listen, I'm a 
detective, only here to solve an old mystery.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 1: "Lies! Leave before you regret it." *He 
comes out from the shadows into your flashlight, revealing a
disproportionate body, and disfigured face.*")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
*You step backwards, face pale and cold sweat dripping down 
the sides of your face.*)" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "What... Who... What are you...? What happened to you?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 1: *distorted* "YOU PEOPLE DID THIS TO ME! TO 
US! You know what you did... And now, you're gonna p-")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 2: "What's with the shouting, 15... OH! It 
seems we have a new friend! Hello~")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 1: "They're not. A friend. You..." *The thing 
inches closer.* "Need to leave now, if you want to live.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Unknown voice 2: "15, we've talked about this...They can't 
ALL be like that... Can't we take this chance to make a new 
friend?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
15 (Survivor): "Are you serious? This isn't a game, 43. How 
could you ever trust one of their kind, when you know just 
as much as me what they did to us? They also threatened me 
with this thing!" *Holds up your pistol.*)" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
43 (Gunman): "If this lovely Detective wanted to hurt us, 
they would have done it by now. You said it yourself. Either 
way, the people who experimented on us looked different. No 
long coats this time. No evil grins, right? There has to be 
good people out there who might understand us. Give them a 
chance, 15.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Hey, 43 is right. I'm not here to hurt anyone. I don't
know who did this to you, but it wasn't me. I'm only here to
investigate what happened here and go. You guys probably know
about this place way more than me. If it's not too much to 
ask, could you tell me what happened? It would be much 
appreciated. Maybe... I could help you too.")" << std::endl;
std::cin.get();
std::cout << R"(-------------------------------------------------------------
15: "First of all, who gave you permission to call us by our 
names? And second, I'm not obliged to tell you anything. I 
plead the fourth.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
43: "But you're always going on and on about the past. Just 
give them a chance... Who knows when we will ever get to go 
outside again?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
15: "43, we talked about this. You have to stop thinking 
that the outside is good when we are treated like dirt.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
15: ...Fine. You want your information so bad? How about 
this? Let’s play some games. If you win… I might give you
some  information. But if you lose… there’s no telling
what will happen. So what do you say, detective?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "That's fine with me."



)" << std::endl; // filler space = a way to signal diag is done :)
std::cin.get();
system("cls");
}

void dialogue::introafterbattlediag() {
	system("cls");
	std::cout << R"(Press Enter to continue . . .
-------------------------------------------------------------
15: "Okay then... I'll start by introducing ourselves. 
If you can't tell, we were the test subjects used in this
lab. They took all of us from our parents when we were 
kids. There used to be way more of us, but unfortunately,
they didn't survive the experiments. There's only a few 
of us remaining. I'm the second oldest, the others call 
me 15 since I was the 15th test subject. 43 is one of the
youngest we have left. The oldest is the first ever test 
subject that arrived here, we refer to him as...")" << std::endl;
	std::cin.get();
	std::cout << R"("Aleksandr")" << std::endl;
	std::cin.get();
	std::cout << R"("Loors")" << std::endl;
	std::cin.get();
	std::cout << R"(“Barnaby”)" << std::endl;
	std::cin.get();
	std::cout << R"("Zhen Xiang")" << std::endl;
	std::cin.get();
	std::cout << R"("Himeko")" << std::endl;
	std::cin.get();
	std::cout << R"("Jungkook")" << std::endl;
	std::cin.get();
	std::cout << R"("Pierre")" << std::endl;
	std::cin.get();
	std::cout << R"("N. Rodríguez I.")" << std::endl;
	std::cin.get();
	std::cout << R"("...")" << std::endl;
	std::cin.get();
	std::cout << R"("But you can call him '01'.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
"You: What does "N." stand for?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
15: "...")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
"*You, in mind:* "Ok... so I'll just call him '01'.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
43: "Bro, WHO are you talking about, 15?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
15: "..."


)" << std::endl;
	std::cin.get();
	system("cls");
}

void dialogue::battle2diag() {
	system("cls");
	std::cout << R"(Press Enter to continue . . .
-------------------------------------------------------------
You: "Why are there little to no files about this laboratory?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
43: "Most of the documentation on what happened was burned 
or thrown away by those scientists. The only thing that 
survived the data wipe was us. According to 01, the scientists
wanted to make us into super humans. In the process of that, 
it turned us into these creatures you see now.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "If that's the case, not to offend you, but why are you 
all so passive?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
43: "We used to be aggressive, but 01 failed in guiding
us regarding our "revenge" plan. There was a time where we 
too felt rage. However, we were quick to realise that we were
not gonna be able to find the same scientists that 
experimented on us. And if anything, we might've been too late
to do so as we learnt that it's been years since the incident
happened. We woke up too late, you see.)" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Ah..."



)" << std::endl;
	std::cin.get();
	system("cls");
}

void dialogue::battle3diag() {
	system("cls");
	std::cout << R"(Press Enter to continue . . .
-------------------------------------------------------------
17 (Grim): "Hey here's a tip, take everything everyone says 
with a grain of salt. I don't like you, but since 15 trusts 
you... I won't question it.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "...")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
17: "What? It's been a long time since any truth was spoken
about so I might as well tell you some. It's not like he 
would let you in on any more secrets.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "You're right. So... why exactly did 01 want revenge? 
I heard a little bit about it from Gunman, but there has to
be more information, right?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Grim: If you truly want to know. As you may have already 
been told, 01 is the first test subject that came to the lab.
From what I've heard, he was deemed as a failed experiment
by the scientists. However, the scientists chose to keep him
alive. 

They kept him throughout the run of the lab because they 
wanted to keep him as a reference. 

He was basically forced to watch as the scientists experiment
on others, causing horrendous things to happen to them. The 
result of that was him growing a strong hatred towards the 
scientists. 

When the scientists eventually abandoned the lab, 01 was able
to break free from his confinement. He wanted to kill those 
scientists that experimented on him and everyone else, hoping
to venture out and find them in order to give them a taste of
their own medicine. 

Though, he knew that if he left, they would of killed him and
us on sight because of what we are and what he wished to do. 
Afraid of risking even more lives, especially since we had no
idea where the scientists could've gone, he decided to keep 
the rest of us at the lab. 

Like what you heard from 43, initially, he planned to train 
us to become strong enough to kill the scientists one day. We
went through a training routine for a good year or so. But as
time went by, he became less willing to continue on with the
revenge.

Instead, he turned to playing games with us as a way to heal
his and our inner child and occupy all of us.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "So to summarise, he just... gave up on killing?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
Grim: "Although he planned everything, he isn't a monster. 
He simply wanted justice."



)" << std::endl;
	std::cin.get();
	system("cls");
}

void dialogue::battle4diag() {
	system("cls");
	std::cout << R"(Press Enter to continue . . .
-------------------------------------------------------------
45 (Trickster): "NOO! HOW DID YOU BEAT ME! DON'T LEAVE 
YET!!!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Woah, calm down. I'm not going to leave so soon. I 
wanted to ask you something. Do you know how old you are?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
45: "Me? 14!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "14? That means you were 7 when this lab was 
abandoned.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
45: "Yep!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "All of you must be really young...")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
45: "Yeah, after all, we were taken when we were very young
for scientists to conduct studies on us. We were treated 
like lab rats! No, we were treated far worse! 

They injected us with unknown substances that would mess with
our blood and body. I even heard someone say that it altered 
our DNA too! I vividly remember what I experienced when it 
was my turn. I would sometimes throw up or get high fevers. 

At some point, I even grew an extra pair of arms! I don’t know
why it didn't stick... I would’ve been so much cooler. Anyway, 
some people died because of the experiments, everyone would
feel woozy every now and then as well... That's also why I 
can read your mind!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Really? What am I thinking of now?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
45: "You're thinking of... the... the door!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Where is it then?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
45: "I'm no navigator! Find it yourself, human!"



)" << std::endl;
	std::cin.get();
	system("cls");
}

void dialogue::battle5diag() {
	system("cls");
	std::cout << R"(Press Enter to continue . . .
              _..----.._    _
            .'  .--.    "-.(0)_
'-.__.-'"'=:|   ,  _)_ \__ . c\'-..
             '''------'---''---'-"      cheese plz
-------------------------------------------------------------
71, 72, 74 (Henchmen): "No way you won!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "What the, why can the rats talk?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
71: "You've been playing games with us, and you didn't
realise? 72, can you believe this guy?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
72: "I can't either, 71. You cannot be that dense!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "You're... literal talking rats, did you expect me
to know that you're fluent?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
74: "Stupid human.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
72: "Be nice, 74. What if he stops playing with us?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Enough! Tell me what I want to know.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
71: "We're rats, why would we know anything?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "...All of you seem to know every little thing 
about this place.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
71: "You seriously can't believe some of us don't 
care about what has been happening?" We just want
games!")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Just answer me.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
74: "Ask your question.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Wait, if you guys are 71, 72 and 74... 
where's 73?")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
71, 72, 74: "...")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
You: "Oh.")" << std::endl;
	std::cin.get();
	std::cout << R"(-------------------------------------------------------------
74: "There, your question's answered. Leave.")" << std::endl;
	std::cin.get();
	system("cls");
}

void dialogue::bossdiag() {
	system("cls");
	std::cout << R"(Press Enter to continue . . .
-------------------------------------------------------------
01: "Are you satisfied with all that you've found out...?")" << std::endl;
	std::cin.get();
	char yesdiag;
	do {
		std::cout << "Yes (Y) or No (N)?" << std::endl;
		std::cin >> yesdiag;
	} while (yesdiag != 'Y' && yesdiag != 'y' && yesdiag != 'N' && yesdiag != 'n');
	if (yesdiag == 'Y' || yesdiag == 'y') {
		std::cout << R"(-------------------------------------------------------------
01: "Please leave then. You don't have any business with us
anymore.")" << std::endl;
		std::cin.get();
	}
	else if (yesdiag == 'N' || yesdiag == 'n') {
		std::cout << R"(-------------------------------------------------------------
01: "What other information would you need? You know what 
happened. Leave us alone.")" << std::endl;
		std::cin.get();
		std::cout << R"(-------------------------------------------------------------
You: "Isn't there something you need to tell me?")" << std::endl;
		std::cin.get();
		std::cout << R"(-------------------------------------------------------------
01: "What?")" << std::endl;
		std::cin.get();
		std::cout << R"(-------------------------------------------------------------
"You: You called me here.")" << std::endl;
		std::cin.get();
		std::cout << R"(-------------------------------------------------------------
"01: ...Fine, it’s over there."



)" << std::endl;
		std::cin.get();
	}
}