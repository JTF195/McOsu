//================ Copyright (c) 2016, PG, All rights reserved. =================//
//
// Purpose:		osu!.db + collection.db + raw loader + scores etc.
//
// $NoKeywords: $osubdb
//===============================================================================//

#ifndef OSUDATABASE_H
#define OSUDATABASE_H

#include "cbase.h"

class Timer;

class Osu;
class OsuBeatmap;
class OsuBeatmapDifficulty;
class OsuFile;

class OsuDatabaseLoader;

class OsuDatabase
{
public:
	struct Collection
	{
		UString name;
		std::vector<std::pair<OsuBeatmap*, std::vector<OsuBeatmapDifficulty*>>> beatmaps;
	};

public:
	OsuDatabase(Osu *osu);
	virtual ~OsuDatabase();
	void reset();

	void update();

	void load();
	void cancel();

	inline float getProgress() {return m_fLoadingProgress;}
	inline int getNumBeatmaps() {return m_beatmaps.size();} // valid beatmaps
	inline std::vector<OsuBeatmap*> getBeatmaps() {return m_beatmaps;}
	inline int getNumCollections() {return m_collections.size();}
	inline std::vector<Collection> getCollections() {return m_collections;}

	bool isFinished() {return getProgress() >= 1.0f;}
	inline bool foundChanges() {return m_bFoundChanges;}

private:
	friend class OsuDatabaseLoader;

	void loadRaw();
	void loadDB(OsuFile *db);

	OsuBeatmap *loadRawBeatmap(UString beatmapPath);

	Osu *m_osu;
	Timer *m_importTimer;
	bool m_bIsFirstLoad;
	bool m_bFoundChanges; // for total refresh detection of raw loading

	// global
	int m_iNumBeatmapsToLoad;
	float m_fLoadingProgress;
	std::vector<OsuBeatmap*> m_beatmaps;

	// osu!.db
	int m_iVersion;
	int m_iFolderCount;
	UString m_sPlayerName;

	// collection.db
	std::vector<Collection> m_collections;

	// raw load
	bool m_bRawBeatmapLoadScheduled;
	int m_iCurRawBeatmapLoadIndex;
	UString m_sRawBeatmapLoadOsuSongFolder;
	std::vector<UString> m_rawBeatmapFolders;
	std::vector<UString> m_rawLoadBeatmapFolders;
};

#endif
