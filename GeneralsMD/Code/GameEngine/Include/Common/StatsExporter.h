/*
**	Command & Conquer Generals Zero Hour(tm)
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

class AsciiString;
class Object;
class Player;
class DamageInfo;

/// Export game statistics as a JSON file to disk alongside the replay file.
/// @param replayDir Directory containing replays (e.g. "[UserDataPath]/Replays/")
/// @param replayFileName Replay filename with extension (e.g. "LastReplay.rep")
void ExportGameStatsJSONToDisk(const AsciiString& replayDir, const AsciiString& replayFileName);

/// Export game statistics for a live match directly into memory, with no disk I/O.
/// Spawns a background thread that assembles the JSON payload, gzip-compresses it
/// in memory, and hands the resulting bytes to the online services manager's stats
/// cache buffer for upload once a destination URL is available.
void ExportGameStatsToMemory(const AsciiString& replayFileName);

/// Joins and clears any background threads spawned by ExportGameStatsToMemory.
/// Call during shutdown before the online services manager is torn down.
void StatsExporterWaitForThreads();

/// Collect a time-series snapshot of all players' stats (called every game logic frame).
/// Snapshots are taken every 30 frames (~1 second) and stored in memory.
void StatsExporterCollectSnapshot();

/// Begin recording stats for a new replay. Activates recording and resets all stored data.
void StatsExporterBeginRecording();

/// Record a kill event with full context (called from Object::scoreTheKill).
void StatsExporterRecordKill(const Object *killer, const Object *victim, const DamageInfo *damageInfo);

/// Record a build event (called from Player::onUnitCreated / onStructureConstructionComplete).
void StatsExporterRecordBuild(const Object *producer, const Object *built);

/// Record a capture event (called from Object::onCapture).
void StatsExporterRecordCapture(const Object *captured, const Player *oldOwner, const Player *newOwner);
