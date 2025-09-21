Todo:
* Either levels with fixed number of enemies or unlimited
* Enemies drop xp
* Leveling system -> pick between 3 things
* Score
* Proper HP and damage - The systems are there I guess
* Player can die/restart
* Enemies dont spawn next to player

After Core ^:
* New enemy types
* Weapon enhancements not just damage or speed
* Powerups like nightmare zone

---

## Suggested Learning Path & Design Challenges

Here are some challenges that build on your ideas and are designed to test the architectural patterns we discussed.

### 1. Health, Damage, and Death

*   **Feature:** Player and enemies have health. Bullets deal damage. Entities are destroyed only when health reaches zero. When the player dies, the game enters a "Game Over" state.
*   **Learning Focus:**
    *   **Data-Driven Systems:** Create a `HealthComponent` and a `DamageComponent`. Your `CollisionHandler` and `WeaponsHandler` will now read damage data and modify health data, instead of just calling `destroy()`.
    *   **Event Bus:** When an entity's health is depleted, the system responsible (e.g., a new `HealthSystem`) should publish a `PlayerDiedEvent` or `EnemyDiedEvent`. This decouples the act of dying from its consequences (like game over screens or dropping loot).
    *   **Game State Management:** Use the `PlayerDiedEvent` to pause the `Physics` and `Gameplay` phases and transition the game to a `GameOver` state.

### 2. Experience Orbs & Player Leveling

*   **Feature:** When an enemy dies, it spawns an "experience orb" entity. When the player collides with an orb, they gain experience points. Reaching a certain threshold triggers a level-up.
*   **Learning Focus:**
    *   **Archetypes:** This is a perfect use for the archetype pattern. Define an `"xp_orb"` archetype in your `EntityManager` that describes what an orb is (e.g., a `RenderableComponent`, a `ColliderComponent`, and an `ExperienceValueComponent`).
    *   **Event-Driven Spawning:** A new `LootSystem` or `ExperienceSystem` can listen for the `EnemyDiedEvent`. When it receives one, it tells the `EntityManager` to `createEntity("xp_orb", enemy_position)`.
    *   **Component Design:** The player entity will need an `ExperienceComponent` to track its current XP and the amount needed for the next level.

### 3. Level-Up Screen & Weapon Upgrades

*   **Feature:** When the player levels up, the game pauses and presents them with 3 choices for an upgrade (e.g., "More Damage," "Faster Fire Rate," or the "Double Shot" we discussed).
*   **Learning Focus:**
    *   **Complex Game State:** This requires a `LevelUpScreen` state that pauses the main game loop (or at least the `Physics` and `Gameplay` phases). Input handling will need to change to navigate the menu.
    *   **Data-Driven Upgrades:** This is a masterclass in data-driven design. An upgrade isn't new code; it's just modifying data. The "Double Shot" upgrade would be implemented by finding the player's `WeaponComponent` and changing its `projectileCount` property from 1 to 2. "More Damage" would modify the `damage` property. The upgrade choices themselves could be defined in a data file and loaded at startup.

### 4. Enemy Variety

*   **Feature:** Introduce new enemy types, like a slow, high-health "Tank" and a fast, fragile "Scout."
*   **Learning Focus:**
    *   **Archetype Power:** With the archetype system in place, this becomes incredibly easy. You would simply define new archetypes (`"tank_enemy"`, `"scout_enemy"`) with different starting values for their `HealthComponent` and `AiComponent` (for speed). Your `EnemySpawner` can then be modified to spawn a mix of different archetype strings.
