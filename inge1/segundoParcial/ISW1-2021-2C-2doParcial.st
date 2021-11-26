!classDefinition: #ConstructionTeamTest category: 'ISW1-2021-2C-2doParcial'!
TestCase subclass: #ConstructionTeamTest
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!ConstructionTeamTest methodsFor: 'test objects' stamp: 'jpm 11/25/2021 20:01:15'!
createDefaultWeatherService

WeatherServiceMock answering: [ :fromDate :aNumberOfDays | ^0 * day]! !

!ConstructionTeamTest methodsFor: 'test objects' stamp: 'jpm 11/25/2021 20:14:35'!
createWeatherServiceAnswering: aNumberOfDays

	^WeatherServiceMock answering: [ :fromDate :anotherNumberOfDays | aNumberOfDays]! !

!ConstructionTeamTest methodsFor: 'test objects' stamp: 'jpm 11/25/2021 18:33:31'!
defaultArea

	^ 20 * (meter^2)! !

!ConstructionTeamTest methodsFor: 'test objects' stamp: 'jpm 11/25/2021 18:33:21'!
defaultAreaBuildingSpeed

 ^self defaultArea / day
! !

!ConstructionTeamTest methodsFor: 'test objects' stamp: 'jpm 11/25/2021 18:33:41'!
defaultPrice

	^20 * dollar.! !

!ConstructionTeamTest methodsFor: 'test objects' stamp: 'jpm 11/25/2021 18:35:02'!
defaultPriceCharged

 ^self defaultPrice / day
! !


!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:40'!
test01FixPriceAndAreaCapacityTeamFinishBuildingInOneDay

	| team teamPrice teamSpeed |
	
	teamPrice := self defaultPriceCharged.
	teamSpeed := self defaultAreaBuildingSpeed.

	team := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed) withWeatherService: self createDefaultWeatherService.
	
	self assert: team builds: self defaultArea in: 1 * day charging: self defaultPriceCharged*day.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:40'!
test02FixPriceAndAreaCapacityTeamFinishBuildingInMoreThanOneDay

	| team teamPrice teamSpeed |
	
	teamPrice := self defaultPriceCharged.
	teamSpeed := self defaultAreaBuildingSpeed.

	team := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed) withWeatherService: self createDefaultWeatherService.
	
	self assert: team builds: (self defaultArea * 3.5) in: 4 * day charging: teamPrice * 4 * day.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:40'!
test03PriceAndDaysCalculationsWorksWhenUsingOtherUnits

	| team teamPrice teamSpeed |
	
	teamPrice := (7 * dollar) / week.
	teamSpeed := 100000 * ((centimeter * centimeter) / day).

	team := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed) withWeatherService: self createDefaultWeatherService.
	
	self assert: team builds: (10 * meter * meter) in: 1 * day charging: 1 * dollar.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:54:15'!
test04CanNotSetPriceWhenRainingLowerOrEqualThanPriceWhenNotRaining

	| nonRainyPrice rainyPrice |
	
	nonRainyPrice := self defaultPriceCharged.
	rainyPrice := nonRainyPrice - (1 * (dollar/day)).
	
	
		
	self should: [
			RainDependentPricePerDay 
				chargingWithoutRain: nonRainyPrice 
				chargingWithRain: rainyPrice.
		] 
		raise: Error - MessageNotUnderstood 
		withExceptionDo: [ :anError |
			self assert: RainDependentPricePerDay notChargingMoreWithRainErrorDescription equals: anError messageText 
			
		] 
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:41'!
test05RainDependentTeamFinishBuildingInMoreThanOneDay

	| team nonRainyPrice rainyPrice rainyDays nonRainyDays teamSpeed |
	
	nonRainyPrice := self defaultPriceCharged.
	rainyPrice := nonRainyPrice * 2.
		
	teamSpeed := self defaultAreaBuildingSpeed.
	rainyDays := 3.
	nonRainyDays := 7.
	
	team := ConstructionTeam 
		withChargingScheme: (RainDependentPricePerDay chargingWithoutRain: nonRainyPrice chargingWithRain: rainyPrice ) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed) withWeatherService: (self createWeatherServiceAnswering: rainyDays * day).
	
	self assert: team builds: (self defaultArea * 10) in: 10 * day charging: ((nonRainyDays * nonRainyPrice) + (rainyDays * rainyPrice)) * day.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:41'!
test06CapacityReductionTeamFinishBuildingAfterCapacityReduction

	| team teamPrice initialTeamSpeed reducedTeamSpeed daysUntilReduction |
	
	teamPrice := self defaultPriceCharged.
	initialTeamSpeed := self defaultAreaBuildingSpeed.
	reducedTeamSpeed := initialTeamSpeed / 2.
	daysUntilReduction := 3 * day.
	
	team := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDayWithOneReduction 
							startingWith: initialTeamSpeed 
							for: daysUntilReduction 
							thenWith: reducedTeamSpeed)
		withWeatherService: self createDefaultWeatherService.
	
	self assert: team builds: (self defaultArea * 5) in: 7 * day charging: teamPrice * 7 * day.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:40'!
test07CapacityReductionTeamFinishBuildingBeforeCapacityReduction

	| team teamPrice initialTeamSpeed reducedTeamSpeed daysUntilReduction |
	
	teamPrice := self defaultPriceCharged.
	initialTeamSpeed := self defaultAreaBuildingSpeed.
	reducedTeamSpeed := initialTeamSpeed / 2.
	daysUntilReduction := 10 * day.
	
	team := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDayWithOneReduction 
							startingWith: initialTeamSpeed 
							for: daysUntilReduction 
							thenWith: reducedTeamSpeed)
		withWeatherService: self createDefaultWeatherService.
	
	self assert: team builds: (self defaultArea * 5) in: 5 * day charging: teamPrice * 5 * day.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:53'!
test08Combining2TeamsWithSameCharacteristicsWorks

	| team1 team2 teamPrice teamSpeed combinedTeam |
	
	teamPrice := self defaultPriceCharged.
	teamSpeed := self defaultAreaBuildingSpeed.
	
	team1 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
		
	team2 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
		
	combinedTeam := CombinedConstructionTeam combining: {team1. team2}.
	
	self assert: combinedTeam builds: (self defaultArea * 10) in: 5 * day charging: teamPrice * 10 * day.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:57:52'!
test09Combining2TeamsWithDifferentCharacteristicsWorks

	| team1 team2 teamPrice teamSpeed combinedTeam |
	
	teamPrice := self defaultPriceCharged.
	teamSpeed := self defaultAreaBuildingSpeed.
	
	team1 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice * 2) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed / 2)
		withWeatherService: self createDefaultWeatherService.
		
	team2 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
		
	combinedTeam := CombinedConstructionTeam combining: {team1. team2}.
	
	self assert: combinedTeam builds: (self defaultArea * 10) in: 10 * day charging: (teamPrice * 10 * 2) + (teamPrice * 5) * day.
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:58:26'!
test10CombiningCombinedTeamsWorks

	| team1 team2 team3 combinedTeam1 megaCombinedTeam teamPrice teamSpeed |
	
	teamPrice := self defaultPriceCharged.
	teamSpeed := self defaultAreaBuildingSpeed.
	
	team1 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
	
	team2 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
	
	team3 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
		
	combinedTeam1 := CombinedConstructionTeam combining: {team1. team2}.
	megaCombinedTeam := CombinedConstructionTeam combining: {combinedTeam1. team3 }.
		
	self assert: megaCombinedTeam builds: (self defaultArea * 10) in: 5 * day charging: ((3 * teamPrice * 2) + (teamPrice * 5)) * day.
	
	! !

!ConstructionTeamTest methodsFor: 'testing' stamp: 'jpm 11/25/2021 21:59:07'!
test11CanNotCombineTwoTeamsThatRepeatATeam
"Este no llegue a hacer que ande por tiempo </3"
	| team1 team2 combinedTeam1 teamPrice teamSpeed |
	
	teamPrice := self defaultPriceCharged.
	teamSpeed := self defaultAreaBuildingSpeed.
	
	team1 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
	
	team2 := ConstructionTeam 
		withChargingScheme: (FixedPricePerDay charging: teamPrice) 
		withBuildingCapacity: (FixedAreaPerDay building: teamSpeed)
		withWeatherService: self createDefaultWeatherService.
		
	combinedTeam1 := CombinedConstructionTeam combining: {team1. team2}.
	self 
		should: [CombinedConstructionTeam combining: {combinedTeam1. team1 }] 
		raise: Error - MessageNotUnderstood 
		withExceptionDo: [ :anError|
			self assert: TeamHolder cantRepeatTeamsWhenCombiningErrorDescription equals: anError messageText.
			] ! !


!ConstructionTeamTest methodsFor: 'assertions' stamp: 'jpm 11/25/2021 18:43:07'!
assert: aTeam builds: anAmountOfSquaredMeters in: aNumberOfDays charging: anAmountOfDollars

	| timeToBuild priceToBuild |
	
	timeToBuild := aTeam daysRequired: anAmountOfSquaredMeters.
	priceToBuild := aTeam dollarsRequired: anAmountOfSquaredMeters.
	
	self assert: aNumberOfDays equals: timeToBuild. 
	self assert: anAmountOfDollars equals: priceToBuild.
	! !


!classDefinition: #ChargingScheme category: 'ISW1-2021-2C-2doParcial'!
Object subclass: #ChargingScheme
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!ChargingScheme methodsFor: 'accesing' stamp: 'jpm 11/25/2021 20:23:25'!
dollarsRequiredFor: aNumberOfdays with: aTeam
	
	^self subclassResponsibility.! !


!classDefinition: #FixedPricePerDay category: 'ISW1-2021-2C-2doParcial'!
ChargingScheme subclass: #FixedPricePerDay
	instanceVariableNames: 'pricePerDay'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!FixedPricePerDay methodsFor: 'initialization' stamp: 'jpm 11/25/2021 18:09:13'!
initializeCharging: aPricePerDay 
	
	pricePerDay := aPricePerDay.! !


!FixedPricePerDay methodsFor: 'accesing' stamp: 'jpm 11/25/2021 18:28:08'!
dollarsRequired: aNumberOfdays 
	
	^pricePerDay * aNumberOfdays.! !

!FixedPricePerDay methodsFor: 'accesing' stamp: 'jpm 11/25/2021 19:50:57'!
dollarsRequiredFor: aNumberOfdays with: aTeam
	
	^aTeam dollarsRequiredWithFixedPriceTeamFor: aNumberOfdays.! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'FixedPricePerDay class' category: 'ISW1-2021-2C-2doParcial'!
FixedPricePerDay class
	instanceVariableNames: ''!

!FixedPricePerDay class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 18:08:52'!
charging: aPricePerDay 

	^self new initializeCharging: aPricePerDay. ! !


!classDefinition: #RainDependentPricePerDay category: 'ISW1-2021-2C-2doParcial'!
ChargingScheme subclass: #RainDependentPricePerDay
	instanceVariableNames: 'priceWhenNotRaining priceWhenRaining'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!RainDependentPricePerDay methodsFor: 'initialization' stamp: 'jpm 11/25/2021 18:57:25'!
initializeChargingWithoutRain: dollarsToChargeWhenItIsNotRaining chargingWithRain: dollarsToChargeWhenItIsRaining 
	
	priceWhenNotRaining := dollarsToChargeWhenItIsNotRaining.
	priceWhenRaining := dollarsToChargeWhenItIsRaining.! !


!RainDependentPricePerDay methodsFor: 'accesing' stamp: 'jpm 11/25/2021 20:11:28'!
dollarsRequiredFor: aNumberOfdays raining: aNumberOfRainyDays

	| effectiveNonRainyDays effectiveRainyDays |
	
	effectiveRainyDays := self effectiveDaysWorkingWithRainWhenRaining: aNumberOfRainyDays of: aNumberOfdays.
	effectiveNonRainyDays := aNumberOfdays - effectiveRainyDays.
	
	^(priceWhenRaining * effectiveRainyDays) + (priceWhenNotRaining * effectiveNonRainyDays).! !

!RainDependentPricePerDay methodsFor: 'accesing' stamp: 'jpm 11/25/2021 19:56:13'!
dollarsRequiredFor: aNumberOfdays with: aTeam
	
	^aTeam dollarsRequiredWithRainDependentTeamFor: aNumberOfdays.! !


!RainDependentPricePerDay methodsFor: 'auxiliar calculations' stamp: 'jpm 11/25/2021 20:08:07'!
effectiveDaysWorkingWithRainWhenRaining: aNumberOfRainyDays of: aNumberOfDays

	^aNumberOfDays min: aNumberOfRainyDays.! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'RainDependentPricePerDay class' category: 'ISW1-2021-2C-2doParcial'!
RainDependentPricePerDay class
	instanceVariableNames: ''!

!RainDependentPricePerDay class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 19:05:42'!
assert: dollarsToChargeWhenItIsNotRaining isLessThan: dollarsToChargeWhenItIsRaining

	^ (dollarsToChargeWhenItIsNotRaining < dollarsToChargeWhenItIsRaining) ifFalse: [self error: self notChargingMoreWithRainErrorDescription]! !

!RainDependentPricePerDay class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 19:05:07'!
chargingWithoutRain: dollarsToChargeWhenItIsNotRaining chargingWithRain: dollarsToChargeWhenItIsRaining 
	
	self assert: dollarsToChargeWhenItIsNotRaining isLessThan: dollarsToChargeWhenItIsRaining.
	
	^self new initializeChargingWithoutRain: dollarsToChargeWhenItIsNotRaining chargingWithRain: dollarsToChargeWhenItIsRaining ! !


!RainDependentPricePerDay class methodsFor: 'error handling' stamp: 'jpm 11/25/2021 19:01:56'!
notChargingMoreWithRainErrorDescription

	^'You are not charging more money for the rainy days, do not let them explode you!!!!!!'! !


!classDefinition: #ConstructionCapacity category: 'ISW1-2021-2C-2doParcial'!
Object subclass: #ConstructionCapacity
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!


!classDefinition: #FixedAreaPerDay category: 'ISW1-2021-2C-2doParcial'!
ConstructionCapacity subclass: #FixedAreaPerDay
	instanceVariableNames: 'squaredMetersPerDay'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!FixedAreaPerDay methodsFor: 'initialization' stamp: 'jpm 11/25/2021 18:13:28'!
initializeBuilding: AnAmountOfSquaredMetersPerDay 

	squaredMetersPerDay := AnAmountOfSquaredMetersPerDay.! !


!FixedAreaPerDay methodsFor: 'as yet unclassified' stamp: 'jpm 11/25/2021 18:44:01'!
daysRequired: anAmountOfSquaredMeters
 
	^(anAmountOfSquaredMeters / squaredMetersPerDay) ceiling.! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'FixedAreaPerDay class' category: 'ISW1-2021-2C-2doParcial'!
FixedAreaPerDay class
	instanceVariableNames: ''!

!FixedAreaPerDay class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 18:12:49'!
building: AnAmountOfSquaredMetersPerDay 

	^self new initializeBuilding: AnAmountOfSquaredMetersPerDay ! !


!FixedAreaPerDay class methodsFor: 'error handling' stamp: 'jpm 11/25/2021 18:09:38'!
error: aString 
	self shouldBeImplemented.! !


!classDefinition: #FixedAreaPerDayWithOneReduction category: 'ISW1-2021-2C-2doParcial'!
ConstructionCapacity subclass: #FixedAreaPerDayWithOneReduction
	instanceVariableNames: 'initialSpeed daysUntilReduction reducedSpeed'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!FixedAreaPerDayWithOneReduction methodsFor: 'initialization' stamp: 'jpm 11/25/2021 20:27:11'!
initializeStartingWith: aInitialSpeed for: aNumberOfDaysUntilSpeedReduction thenWith: aReducedSpeed 
	
	initialSpeed := aInitialSpeed.
	daysUntilReduction := aNumberOfDaysUntilSpeedReduction.
	reducedSpeed := aReducedSpeed.! !


!FixedAreaPerDayWithOneReduction methodsFor: 'as yet unclassified' stamp: 'jpm 11/25/2021 20:43:08'!
daysRequired: anAreaToBuild
 
	| areaBuiltAtInitialSpeed areaLeftForReducedSpeed daysWorkingAtReducedSpeed daysWorkingAtInitialSpeed |
	
	areaBuiltAtInitialSpeed := anAreaToBuild min: (initialSpeed * daysUntilReduction).
	areaLeftForReducedSpeed := anAreaToBuild - areaBuiltAtInitialSpeed.
	daysWorkingAtReducedSpeed := areaLeftForReducedSpeed / reducedSpeed.
	daysWorkingAtInitialSpeed := areaBuiltAtInitialSpeed / initialSpeed.
	
	^daysWorkingAtInitialSpeed + daysWorkingAtReducedSpeed.! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'FixedAreaPerDayWithOneReduction class' category: 'ISW1-2021-2C-2doParcial'!
FixedAreaPerDayWithOneReduction class
	instanceVariableNames: ''!

!FixedAreaPerDayWithOneReduction class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 20:26:37'!
startingWith: aInitialSpeed for: aNumberOfDaysUntilSpeedReduction thenWith: aReducedSpeed 

	^self new initializeStartingWith: aInitialSpeed for: aNumberOfDaysUntilSpeedReduction thenWith: aReducedSpeed ! !


!classDefinition: #TeamHolder category: 'ISW1-2021-2C-2doParcial'!
Object subclass: #TeamHolder
	instanceVariableNames: 'formOfPayment buildingCapacity weatherService'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'TeamHolder class' category: 'ISW1-2021-2C-2doParcial'!
TeamHolder class
	instanceVariableNames: ''!

!TeamHolder class methodsFor: 'error handling' stamp: 'jpm 11/25/2021 21:18:55'!
cantRepeatTeamsWhenCombiningErrorDescription

	^'Can not repeat teams when combining!!!!!!'! !


!classDefinition: #CombinedConstructionTeam category: 'ISW1-2021-2C-2doParcial'!
TeamHolder subclass: #CombinedConstructionTeam
	instanceVariableNames: 'teams'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!CombinedConstructionTeam methodsFor: 'initialization' stamp: 'jpm 11/25/2021 21:57:24'!
initializeCombining: aCollectionOfTeams 
	
	teams := aCollectionOfTeams.! !


!CombinedConstructionTeam methodsFor: 'time queries' stamp: 'jpm 11/25/2021 21:10:26'!
daysRequired: anAreaToBuild
 	
	| areaPerTeam |
	
	areaPerTeam := anAreaToBuild / self totalTeams.
	^teams max: [ :aTeam | aTeam daysRequired: areaPerTeam].! !


!CombinedConstructionTeam methodsFor: 'cost queries' stamp: 'jpm 11/25/2021 21:11:55'!
dollarsRequired: anAreaToBuild
 
	| areaPerTeam |
	areaPerTeam := anAreaToBuild / self totalTeams.
	
	^teams sum: [:aTeam | aTeam dollarsRequired: areaPerTeam] ifEmpty: [0].! !


!CombinedConstructionTeam methodsFor: 'as yet unclassified' stamp: 'jpm 11/25/2021 21:48:01'!
doesNotContain: searchingTeam

	^teams noneSatisfy: [:aTeam| aTeam doesNotContain: searchingTeam]! !

!CombinedConstructionTeam methodsFor: 'as yet unclassified' stamp: 'jpm 11/25/2021 21:09:32'!
totalTeams

	^teams size.! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'CombinedConstructionTeam class' category: 'ISW1-2021-2C-2doParcial'!
CombinedConstructionTeam class
	instanceVariableNames: ''!

!CombinedConstructionTeam class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 21:46:12'!
assertThereIsNotRepetitions: aCollectionOfTeams

	| totalTeams |

	totalTeams := aCollectionOfTeams size.
	1 to: totalTeams do: [ :teamIndex | | team |
		
		team := aCollectionOfTeams at: teamIndex.
		
		1 to: totalTeams do: [:anotherTeamIndex | | anotherTeam |
			
			anotherTeam := aCollectionOfTeams at: anotherTeamIndex.
			
			teamIndex = anotherTeamIndex ifFalse: [
				self assert: (team doesNotContain: anotherTeam).
				]
			] 
		].! !

!CombinedConstructionTeam class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 21:36:25'!
combining: aCollectionOfTeams

	self assertThereIsNotRepetitions: aCollectionOfTeams.
	
	^self new initializeCombining: aCollectionOfTeams ! !


!classDefinition: #ConstructionTeam category: 'ISW1-2021-2C-2doParcial'!
TeamHolder subclass: #ConstructionTeam
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!ConstructionTeam methodsFor: 'initialization' stamp: 'jpm 11/25/2021 21:50:46'!
doesNotContain: searchingTeam

	^(self = searchingTeam) not! !

!ConstructionTeam methodsFor: 'initialization' stamp: 'jpm 11/25/2021 19:54:41'!
initializeWithFormOfPayment: aFormOfPayment withBuildingCapacity: aBuildingCapacity withWeatherService: aWeatherService  
	
	formOfPayment := aFormOfPayment.
	buildingCapacity := aBuildingCapacity.
	weatherService := aWeatherService.! !


!ConstructionTeam methodsFor: 'time queries' stamp: 'jpm 11/25/2021 18:17:18'!
daysRequired: anAmountOfSquaredMeters 
	
	^buildingCapacity daysRequired: anAmountOfSquaredMeters.! !


!ConstructionTeam methodsFor: 'price queries' stamp: 'jpm 11/25/2021 19:47:20'!
dollarsRequired: anAmountOfSquaredMeters 
	
	| daysRequired |
	
	daysRequired := self daysRequired: anAmountOfSquaredMeters.
	^formOfPayment dollarsRequiredFor: daysRequired with: self.! !

!ConstructionTeam methodsFor: 'price queries' stamp: 'jpm 11/25/2021 19:48:43'!
dollarsRequiredWithFixedPriceTeamFor: aNumberOfDays 
	
	^formOfPayment dollarsRequired: aNumberOfDays.! !

!ConstructionTeam methodsFor: 'price queries' stamp: 'jpm 11/25/2021 20:15:07'!
dollarsRequiredWithRainDependentTeamFor: aNumberOfDays
	
	^formOfPayment dollarsRequiredFor: aNumberOfDays raining: (weatherService rainyDaysFrom: Date today totalDays: aNumberOfDays ).! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'ConstructionTeam class' category: 'ISW1-2021-2C-2doParcial'!
ConstructionTeam class
	instanceVariableNames: ''!

!ConstructionTeam class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 20:58:04'!
combining: anArray 
	"DO NOT FORGET TO RENAME COLLABORATORS AND REMOVE THIS COMMENT!!!!"
	self shouldBeImplemented.
	^self new initializeCombining: anArray ! !

!ConstructionTeam class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 19:53:18'!
withChargingScheme: aFormOfPayment withBuildingCapacity: aBuildingCapacity withWeatherService: aWeatherService 
	
	^self new initializeWithFormOfPayment: aFormOfPayment withBuildingCapacity: aBuildingCapacity withWeatherService: aWeatherService.! !


!classDefinition: #WeatherServiceMock category: 'ISW1-2021-2C-2doParcial'!
Object subclass: #WeatherServiceMock
	instanceVariableNames: 'answer'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-2doParcial'!

!WeatherServiceMock methodsFor: 'as yet unclassified' stamp: 'jpm 11/25/2021 19:29:53'!
initializeAnswering: answerClosure
	
	answer := answerClosure.! !

!WeatherServiceMock methodsFor: 'as yet unclassified' stamp: 'jpm 11/25/2021 20:00:43'!
rainyDaysFrom: aFromDate totalDays: aNumberOfDays

	^answer value: aFromDate value: aNumberOfDays.! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'WeatherServiceMock class' category: 'ISW1-2021-2C-2doParcial'!
WeatherServiceMock class
	instanceVariableNames: ''!

!WeatherServiceMock class methodsFor: 'instance creation' stamp: 'jpm 11/25/2021 19:30:58'!
answering: answerClosure

	^self new initializeAnswering: answerClosure. 
	! !
