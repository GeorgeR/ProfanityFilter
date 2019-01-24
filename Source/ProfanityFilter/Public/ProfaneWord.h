#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ProfaneWord.generated.h"

USTRUCT(BlueprintType)
struct PROFANITYFILTER_API FProfaneWord
	: public FTableRowBase
{
	GENERATED_BODY()

public:
	/** The language (for localization) */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName Language;

	/** Where 0 is the most severe */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	uint8 Severity;

	/** The word itself */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Word;

	FProfaneWord();
};