#pragma once
#ifndef VIEW_H
#define VIEW_H

class view
{
public:
	virtual void process() = 0;
	virtual void responce() = 0;
};

#endif // !VIEW_H