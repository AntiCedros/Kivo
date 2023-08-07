CREATE TABLE IF NOT EXISTS "Ingredients" (
	"IngredientID"	INTEGER NOT NULL UNIQUE,
	"IngredientName"	TEXT NOT NULL UNIQUE,
	PRIMARY KEY("IngredientID" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "Recipes" (
	"RecipeID"	INTEGER NOT NULL UNIQUE,
	"RecipeName"	TEXT NOT NULL,
	PRIMARY KEY("RecipeID" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "Locales" (
	"LocaleID"	TEXT NOT NULL UNIQUE,
	PRIMARY KEY("LocaleID")
);
CREATE TABLE IF NOT EXISTS "Localization_Ingredients" (
	"IngredientID"	INTEGER NOT NULL,
	"LanguageID"	TEXT NOT NULL,
	"Translation"	TEXT,
	"IsMain"	INTEGER,
	FOREIGN KEY("LanguageID") REFERENCES "Locales"("LocaleID"),
	FOREIGN KEY("IngredientID") REFERENCES "Ingredients"("IngredientID")
);
CREATE TABLE IF NOT EXISTS "Localization_Ingredient_Info" (
	"IngredientID"	INTEGER NOT NULL,
	"LocaleID"	TEXT NOT NULL,
	"Translation"	TEXT,
	FOREIGN KEY("IngredientID") REFERENCES "Ingredients"("IngredientID"),
	FOREIGN KEY("LocaleID") REFERENCES "Locales"("LocaleID")
);
DELETE FROM sqlite_sequence;
COMMIT;
