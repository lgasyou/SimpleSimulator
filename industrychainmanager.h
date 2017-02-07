#ifndef INDUSTRYCHAINMANAGER_H
#define INDUSTRYCHAINMANAGER_H

// This class contains the industry chain of this game.
class IndustryChainManager {
public:
	static IndustryChainManager &instance();

private:
	IndustryChainManager();;
	~IndustryChainManager();
	IndustryChainManager(const IndustryChainManager &) = delete;
	IndustryChainManager &operator=(const IndustryChainManager &) = delete;
};
#endif // !INDUSTRYCHAINMANAGER_H
