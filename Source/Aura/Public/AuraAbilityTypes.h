#pragma once
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsCriticalHit() const {return bIsCriticalHit;}
	bool IsBlockedHit() const {return bIsBlockedHit;}

	void SetIsCriticalHit(bool InIsCriticalHit){bIsCriticalHit = InIsCriticalHit;}
	void SetIsBlockedHit(bool InIsBlockedHit){bIsBlockedHit = InIsBlockedHit;}
	
	/*returns the actual struct used for serialization, subclasses must overrid this*/
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}
	/**serialization, subclass must override*/
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

protected:

	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsBlockedHit = false;
	
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};


