#include "ProfanityFilterFunctionLibrary.h"
#include "Engine/DataTable.h"

TArray<FProfaneWord> UProfanityFilterFunctionLibrary::CachedWords = TArray<FProfaneWord>();
FName UProfanityFilterFunctionLibrary::DatatablePath = TEXT("DataTable'/ProfanityFilter/DT_WordList.DT_WordList'");

bool UProfanityFilterFunctionLibrary::ContainsProfanity_Name(FName InName, uint8 InMinimumSeverity)
{
	return ContainsProfanity_String(InName.ToString(), InMinimumSeverity);
}

bool UProfanityFilterFunctionLibrary::ContainsProfanity_String(FString InString, uint8 InMinimumSeverity)
{
	LoadCache();

	for (auto& Word : CachedWords)
		if (Word.Severity >= InMinimumSeverity)
			if (InString.Contains(Word.Word, ESearchCase::IgnoreCase))
				return true;

	return false;
}

bool UProfanityFilterFunctionLibrary::ContainsProfanity_Text(FText InText, uint8 InMinimumSeverity)
{
	return ContainsProfanity_String(InText.ToString(), InMinimumSeverity);
}

template <>
bool UProfanityFilterFunctionLibrary::ContainsProfanity<FString>(FString InString, uint8 InMinimumSeverity)
{
	return ContainsProfanity_String(InString, InMinimumSeverity);
}

void UProfanityFilterFunctionLibrary::LoadCache()
{
	if(CachedWords.Num() > 0)
		return;

	UDataTable* Datatable = LoadObject<UDataTable>(nullptr, *DatatablePath.ToString());
	TArray<FProfaneWord*> Rows;
	const FString Context;
	Datatable->GetAllRows<FProfaneWord>(Context, Rows);
	for (auto& Row : Rows)
		CachedWords.Add(*Row);
}
