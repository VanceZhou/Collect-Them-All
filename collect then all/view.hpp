#ifndef VIEW_HPP
#define VIEW_HPP

#include <string>
#include <vector>

/**
 * I don't think you will have any reason to modify this file
 * or view.cpp.
 */

class View
{
public:
    View(int height, int width);
    virtual ~View() = default;

    View(const View&) = delete;
    View& operator=(const View&) = delete;

    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }
    std::vector<std::string> getView() {return wholeView;}
    /**
     * Output each line of the given vector.
     * What exactly is meant by "output" is up to the subclass.
     */
    virtual void draw(const std::vector<std::string>& lines) = 0;
    
protected:
    int mHeight;
    int mWidth; 
    std::vector<std::string> wholeView;
private:

};

#endif // VIEW_HPP
