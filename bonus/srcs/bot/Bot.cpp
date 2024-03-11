#include "../../headers/Bot.hpp"

Bot::Bot(int clientSocket, std::string buffer, std::string clientIP)
{
	this->clientSocket = clientSocket;
	this->buffer = buffer;
	this->clientIP = clientIP;
	parseBuffer();
}

void	Bot::mySend(const char *msg)
{
	send(clientSocket, msg, std::strlen(msg), 0);
}

void	Bot::parseBuffer()
{
	size_t		i = 4;
	int			j = 0;
	std::string	param;
	std::string	format;
	int			flag = 0;

	while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		i++;
	while (buffer[i]) {
		param.resize(j + 1);
		param[j++] = buffer[i++];
	}
	param.resize(j - 1);
	for (i = 0; i < param.length(); i++) {
		if (param[i] == '\t' || param[i] == '\r' || param[i] == '\n')
			flag++;
	}
	if (flag)
		param.resize(j - 2);
	if (param == "fact") {
		randomFactsGenerator();
		return ;
	}
	else if (param == "weather") {
		format = ":" + clientIP + " 911 " + " " + tostring(clientSocket) + " :Look at the sky and tell me idiot!\r\t\n";
		mySend(format.c_str());
		return ;
	}
	else {
		format = ":" + clientIP + " 911 " + " " + tostring(clientSocket) + " :What?!! You speaking chinese, dummy?!\r\t\n";
		mySend(format.c_str());
		return ;
	}
}

void	Bot::randomFactsGenerator()
{
	srand(time(0));
	std::string	fact;
	int			randNumber = rand() % 15;
	std::string	format;

	switch (randNumber)
	{
	case 0:
		fact = ":Did you know that, Avocados are a fruit, not a vegetable. They're technically considered a single-seeded berry, believe it or not.";
		break;
	case 1:
		fact = ":Did you know that, the Eiffel Tower can be 15 cm taller during the summer, due to thermal expansion meaning the iron heats up, the particles gain kinetic energy and take up more space.";
		break;
	case 2:
		fact = ":Did you know that, Trypophobia is the fear of closely-packed holes. Or more specifically, \"an aversion to the sight of irregular patterns or clusters of small holes or bumps.\" No crumpets for them, then.";
		break;
	case 3:
		fact = ":Did you know that, Allodoxaphobia is the fear of other people's opinions. It's a rare social phobia that's characterised by an irrational and overwhelming fear of what other people think.";
		break;
	case 4:
		fact = ":Did you know that, Australia is wider than the moon. The moon sits at 3400km in diameter, while Australia's diameter from east to west is almost 4000km.";
		break;
	case 5:
		fact = ":Did you know that, 'Mellifluous' is a sound that is pleasingly smooth and musical to hear.";
		break;
	case 6:
		fact = ":Did you know that, The Spice Girls were originally a band called Touch. \"When we first started [with the name Touch], we were pretty bland,\" Mel C told The Guardian in 2018. \"We felt like we had to fit into a mould.\"";
		break;
	case 7:
		fact = ":Did you know that, Emma Bunton auditioned for the role of Bianca Butcher in Eastenders. Baby Spice already had a small part in the soap back in the 90s but tried out for a full-time role. She was pipped to the post by Patsy Palmer but ended up auditioning for the Spice Girls not long after.";
		break;
	case 8:
		fact = ":Did you know that, Human teeth are the only part of the body that cannot heal themselves. Teeth are coated in enamel which is not a living tissue.";
		break;
	case 9:
		fact = ":Did you know that, It's illegal to own just one guinea pig in Switzerland. It's considered animal abuse because they're social beings and get lonely.";
		break;
	case 10:
		fact = ":Did you know that, The Ancient Romans used to drop a piece of toast into their wine for good health - hence why we 'raise a toast'.";
		break;
	case 11:
		fact = ":Did you know that, The heart of a shrimp is located in its head. They also have an open circulatory system, which means they have no arteries and their organs float directly in blood.";
		break;
	case 12:
		fact = ":Did you know that, Amy Poehler was only seven years older than Rachel McAdams when she took on the role of \"cool mom\" in Mean Girls. Rachel was 25 as Regina George - Amy was 32 as her mum.";
		break;
	case 13:
		fact = ":Did you know that, People are more creative in the shower. When we take a warm shower, we experience an increased dopamine flow that makes us more creative.";
		break;
	case 14:
		fact = ":Did you know that, Baby rabbits are called kits. Cute!";
		break;
	
	default:
		fact = "Didnt your momma teach you that asking too many questions is rude kiddo?";
		break;
	}
	format = ":" + clientIP + " 911 " + " " + tostring(clientSocket) + " " + fact + "\r\t\n";
	mySend(format.c_str());
}
