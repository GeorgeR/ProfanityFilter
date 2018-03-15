#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProfaneWord.h"

#include "ProfanityFilterFunctionLibrary.generated.h"

UCLASS()
class PROFANITYFILTER_API UProfanityFilterFunctionLibrary 
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Profanity Filter", meta = (DisplayName = "ContainsProfanity"))
	static bool ContainsProfanity_Name(FName InName, uint8 InMinimumSeverity = 50);

	UFUNCTION(BlueprintCallable, Category = "Profanity Filter", meta = (DisplayName = "ContainsProfanity"))
	static bool ContainsProfanity_String(FString InString, uint8 InMinimumSeverity = 50);

	UFUNCTION(BlueprintCallable, Category = "Profanity Filter", meta = (DisplayName = "ContainsProfanity"))
	static bool ContainsProfanity_Text(FText InText, uint8 InMinimumSeverity = 50);
	
	template <typename TString>
	static bool ContainsProfanity(TString InString, uint8 InMinimumSeverity = 50);

	template <>
	static bool ContainsProfanity(FString InString, uint8 InMinimumSeverity);

private:
	static FName DatatablePath;
	static TArray<FProfaneWord> CachedWords;
	
	static void LoadCache();
};

template <typename TString>
bool UProfanityFilterFunctionLibrary::ContainsProfanity(TString InString, uint8 InMinimumSeverity)
{
	return ContainsProfanity_String(InString.ToString(), InMinimumSeverity);
}