#ifndef TEXT_H
#define TEXT_H


extern cTexture streamedText;
extern void textStream(std::string tts);
extern void renderTextStream(SDL_Rect camera);
extern TTF_Font *tsFont;
extern SDL_Rect tsClip[1];
#endif //TEXT_H
