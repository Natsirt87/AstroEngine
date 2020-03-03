#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utilities.h"

/* Parent abstract class of all resource managers, does all
the resource management stuff.*/

template<typename Derived, typename T>
class ResourceManager
{
public:
	ResourceManager(const std::string& pathsFile) //Loads a file that has references to the paths for resources w/ IDs
	{
		loadPaths(pathsFile);
	}

	virtual ~ResourceManager() { PurgeResources(); }

	T* GetResource(const std::string& id) //Returns a reference to a resource given its ID if it exists
	{
		auto res = find(id);
		return(res ? res->first : nullptr);
	}

	std::string GetPath(const std::string& id) //Returns the path to a resource given its ID if it exists
	{
		auto path = m_paths.find(id);
		return(path != m_paths.end() ? path->second : "");
	}

	bool RequireResource(const std::string& id) //Loads an instance of a resource if it exists, given its ID
	{
		auto res = find(id);
		if (res)
		{
			++res->second;
			return true;
		}
		std::cout << "Loading resource " << id << std::endl;
		auto path = m_paths.find(id);
		if (path == m_paths.end()) { return false; }
		T* resource = Load(path->second);
		if (!resource) { return false; }
		m_resources.emplace(id, std::make_pair(resource, 1));
		return true;
	}

	bool ReleaseResource(const std::string& id) //Removes an instance of a resource if it exists, given its ID
	{
		auto res = find(id);
		if (!res) { return false; }
		--res->second;
		if (!res->second) { unload(id); }
		return true;
	}

	void PurgeResources() //Releases all resource instances
	{
		std::cout << "Purging all resources:" << std::endl;
		while (m_resources.begin() != m_resources.end())
		{
			std::cout << "Removing: "
				<< m_resources.begin()->first << std::endl;

			delete m_resources.begin()->second.first;
			m_resources.erase(m_resources.begin());
		}
		std::cout << "Purging finished" << std::endl;
	}

protected:
	T* Load(const std::string& path) //Loads a resource given a path
	{
		return static_cast<Derived*>(this)->Load(path);
	}

private:
	std::pair<T*, unsigned int>* find(const std::string& id) //Find helper method
	{
		auto itr = m_resources.find(id);
		return (itr != m_resources.end() ? &itr->second : nullptr);
	}

	bool unload(const std::string& id) //Helper method for unloading resources
	{
		auto itr = m_resources.find(id);
		if (itr == m_resources.end()) { return false; }
		delete itr->second.first;
		m_resources.erase(itr);
		return true;
	}

	void loadPaths(const std::string& pathFile) //Loads the paths and IDs (names) of all resources from a file
	{
		std::cout << "Initializing texture resources... ";
		std::ifstream paths;
		paths.open(pathFile);

		if (paths.is_open())
		{
			std::string line;

			while (std::getline(paths, line))
			{
				std::stringstream keystream(line);
				std::string pathName;
				std::string path;
				keystream >> pathName;
				keystream >> path;
				m_paths.emplace(pathName, path);
			}
			std::cout << "done." << std::endl;
			paths.close();
			return;
		}
		std::cerr << "! Failed loading path file: " << pathFile << std::endl;
	}

	std::unordered_map<std::string,
		std::pair<T*, unsigned int>> m_resources;
	std::unordered_map<std::string, std::string> m_paths;
};

