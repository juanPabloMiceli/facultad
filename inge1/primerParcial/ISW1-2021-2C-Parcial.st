!classDefinition: #CityTest category: 'ISW1-2021-2C-1erParcial'!
TestCase subclass: #CityTest
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!CityTest methodsFor: 'zone creation' stamp: 'jpm 9/23/2021 18:48:19'!
commercialZone

	^ Commercial new.! !

!CityTest methodsFor: 'zone creation' stamp: 'jpm 9/23/2021 17:45:22'!
industrialZone

	^ Industrial new.! !

!CityTest methodsFor: 'zone creation' stamp: 'jpm 9/23/2021 17:45:29'!
residentialZone

	^ Residential new.! !


!CityTest methodsFor: 'service creation' stamp: 'jpm 9/23/2021 18:06:34'!
solarPlant

	^ SolarPlant new.! !

!CityTest methodsFor: 'service creation' stamp: 'jpm 9/23/2021 18:06:43'!
waterTower

	^ WaterTower new.! !


!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:34:35'!
test01CityWithoutPowerServicesHaveZeroEnergyProduced

	| city |
	
	city := self cityWithServices: {} andZones: {}. 
	
	self  assert: 
			0 
		equals: 
			city energyProduced.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:35:58'!
test02CityWithSolarPlantWithoutZonesHave500EnergyAvailable

	| city |
	
	city := self cityWithServices: {
				self solarPlant
				} 
			  andZones: {}.

	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction 
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:36:47'!
test03CityWithSolarPlantWithResidentialZonesHave495EnergyAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone 
			   }.
				
	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction - self residentialZoneEnergyConsumptionPerCell
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:37:29'!
test04CityWithSolarPlantWithCommertialZonesHave492EnergyAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone.
				self commercialZone.
			  }.
	
	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction - self residentialZoneEnergyConsumptionPerCell  - self commercialZoneEnergyConsumptionPerCell 
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:38:07'!
test05CityWithSolarPlantWithIndustrialZonesHave490EnergyAvailable

	| city |
	
	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self industrialZone.
			  }.
	
	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction - self industrialZoneEnergyConsumptionPerCell 
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:38:58'!
test06CityWithSolarPlantWithServeralZonesImpactEnergyAvailable

	| city |
	
	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone.
				self commercialZone.
				self industrialZone.
				self industrialZone.
			  }.
	
	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction - self residentialZoneEnergyConsumptionPerCell - self commercialZoneEnergyConsumptionPerCell 
			- ( 2 * self industrialZoneEnergyConsumptionPerCell ) 
		equals: 	
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:05:16'!
test07CityWithoutWaterServicesHaveZeroWaterProduced

	| city |

	city := self cityWithServices: {} andZones: {}. 
	
	self  assert: 
			self emptyCityWaterAvailable 
		equals: 
			city waterProduced.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:39:53'!
test08CityWithWaterTowerWithoutZonesHave200WaterAvailable

	| city |

	city := self cityWithServices: {
				self waterTower.
			  } andZones: {}.
	
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction 
		equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:40:27'!
test09CityWithWaterTowerWithResidentialZonesHave191WaterAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone.
			  }.
	
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction - self residentialZoneWaterConsumptionPerCell
		equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:40:55'!
test10CityWithWaterTowerWithCommertialZonesHave198WaterAvailable

	| city |
	
	city _ self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone.
				self commercialZone.
			 }.
				
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction - self residentialZoneWaterConsumptionPerCell - self commercialZoneWaterConsumptionPerCell 
		 equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:41:33'!
test11CityWithWaterTowerWithIndustrialZonesHave190WaterAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self industrialZone.
			  }.
			
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction - self industrialZoneWaterConsumptionPerCell
		equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:42:13'!
test12CityWithWaterTowerWithServeralZonesImpactWaterAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone.
				self commercialZone.
				self industrialZone.
				self industrialZone
			  }.
				
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction - self residentialZoneWaterConsumptionPerCell - self commercialZoneWaterConsumptionPerCell 
			- (2 * self industrialZoneWaterConsumptionPerCell )
		equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:42:45'!
test13CityWith2SolarPlantsHaveTwiceEnergyAvailable

	| city |

	city := self cityWithServices: {
				self solarPlant.
				self solarPlant
			  } 
			  andZones: {}.
			
	self  assert: 
			self emptyCityEnergyAvailable + (2 * self solarPlantProduction) 
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:43:11'!
test14CityWith2WaterTowerHaveTwiceWaterAvailable

	| city |

	city := self cityWithServices: {
				self waterTower.
				self waterTower
			  } 
			  andZones: {}.
	
	self  assert: 
			self emptyCityWaterAvailable + (2 * self waterTowerProduction ) 
		equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 21:00:09'!
test15AResidentialZoneCannotBeAddedWithoutEnergyAndWaterAvailable
	
	self assertZoneCannotBeAddedWithoutEnergyAndWaterAvailable: self residentialZone.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 21:00:18'!
test16ACommertialZoneCannotBeAddedWithoutEnergyAndWaterAvailable

	self assertZoneCannotBeAddedWithoutEnergyAndWaterAvailable: self commercialZone.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 21:00:29'!
test17AnIndustrialZoneCannotBeAddedWithoutEnergyAndWaterAvailable

	self assertZoneCannotBeAddedWithoutEnergyAndWaterAvailable: self industrialZone.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:43:44'!
test18CityWithoutZonesHaveZeroEnergyConsumption

	| city |

	city := self cityWithServices: {} andZones: {}.
	
	self  assert: 
			self emptyCityEnergyAvailable 
		equals: 
			city energyConsumption.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 19:01:24'!
test19CityWithoutResidentialZonesCannotAddCommertialZone

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {}.
	
	self 
		should: [ city addZone: self commercialZone ] 
		raise: Error
		withExceptionDo: [ :error | 
			self assert: error messageText equals: City cannotAddCommertialZoneErrorDescription.
			self assert: 0 equals: city zones size ]! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:44:40'!
test20CityWithSolarPlantWithResidentialZoneWithManyCellsHave10LessEnergyAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
			  	self residentialZone setNumberOfCells: 2.
			  }.
	
	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction - (2 * self residentialZoneEnergyConsumptionPerCell )
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:45:26'!
test21CityWithSolarPlantWithCommertialZoneWithManyCellsHave16LessEnergyAvailable

	| city |
	

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
			  	self residentialZone.
				self commercialZone setNumberOfCells: 2.
			  }.
	
	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction - self residentialZoneEnergyConsumptionPerCell - (2 * self commercialZoneEnergyConsumptionPerCell )
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:45:58'!
test22CityWithSolarPlantWithIndustrialZoneWithManyCellsHave20LessEnergyAvailable

	| city |

	city:= self cityWithASolarPlantAndAWaterTowerAndZones: {
				self industrialZone setNumberOfCells: 2.
			 }.
	
	self  assert: 
			self emptyCityEnergyAvailable + self solarPlantProduction - (2 * self industrialZoneEnergyConsumptionPerCell )
		equals: 
			city energyAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:46:31'!
test23CityWithWaterTowerWithResidentialZoneWithManyCellsHave18LessWaterAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone setNumberOfCells: 2
			  }.
	
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction - (2 * self residentialZoneWaterConsumptionPerCell )
		equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:47:03'!
test24CityWithWaterTowerWithCommertialZoneWithManyCellsHave4LessWaterAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self residentialZone.
				self commercialZone setNumberOfCells: 2
			  }.
	
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction - self residentialZoneWaterConsumptionPerCell  - (2 * self commercialZoneWaterConsumptionPerCell )
		equals: 
			city waterAvailable.! !

!CityTest methodsFor: 'testing' stamp: 'jpm 9/23/2021 20:47:45'!
test25CityWithWaterTowerWithIndustrialZoneWithManyCellsHave20LessWaterAvailable

	| city |

	city := self cityWithASolarPlantAndAWaterTowerAndZones: {
				self industrialZone setNumberOfCells: 2.
			  }.
	
	self  assert: 
			self emptyCityWaterAvailable + self waterTowerProduction - (2 * self industrialZoneWaterConsumptionPerCell )
		equals: 
			city waterAvailable.! !


!CityTest methodsFor: 'zone consumption' stamp: 'jpm 9/23/2021 20:23:15'!
commercialZoneEnergyConsumptionPerCell

	^8 * ep .! !

!CityTest methodsFor: 'zone consumption' stamp: 'jpm 9/23/2021 20:22:51'!
commercialZoneWaterConsumptionPerCell

	^2 * wp.! !

!CityTest methodsFor: 'zone consumption' stamp: 'jpm 9/23/2021 20:23:36'!
industrialZoneEnergyConsumptionPerCell

	^ 10 * ep.! !

!CityTest methodsFor: 'zone consumption' stamp: 'jpm 9/23/2021 20:23:45'!
industrialZoneWaterConsumptionPerCell

	^ 10 * wp.! !

!CityTest methodsFor: 'zone consumption' stamp: 'jpm 9/23/2021 20:24:23'!
residentialZoneEnergyConsumptionPerCell

	^5 * ep.! !

!CityTest methodsFor: 'zone consumption' stamp: 'jpm 9/23/2021 20:24:08'!
residentialZoneWaterConsumptionPerCell

	^ 9 * wp.! !


!CityTest methodsFor: 'service production' stamp: 'jpm 9/23/2021 20:33:30'!
solarPlantProduction

	^500 * ep.  ! !

!CityTest methodsFor: 'service production' stamp: 'jpm 9/23/2021 20:33:46'!
waterTowerProduction

	^200 * wp.  ! !


!CityTest methodsFor: 'city supplies' stamp: 'jpm 9/23/2021 20:35:30'!
emptyCityEnergyAvailable
	
	^ 0 * ep.! !

!CityTest methodsFor: 'city supplies' stamp: 'jpm 9/23/2021 20:35:22'!
emptyCityWaterAvailable
	
	^ 0 * wp.! !


!CityTest methodsFor: 'assertions' stamp: 'jpm 9/23/2021 20:59:16'!
assertZoneCannotBeAddedWithoutEnergyAndWaterAvailable: aZone

	| city |

	city := self cityWithServices: {} andZones: {}.
	
	self 
		should: [ city addZone: aZone. ] 
		raise: Error
		withExceptionDo: [ :error | 
			self assert: error messageText equals: City cannotAddZoneErrorDescription.
			self assert: 0 equals: city zones size]
		! !


!CityTest methodsFor: 'city creation' stamp: 'jpm 9/23/2021 18:52:18'!
cityWithASolarPlantAndAWaterTowerAndZones: aCollectionOfZones

	| aCity |
	
	aCity := City new.
	
	aCity addService: self solarPlant.
	aCity addService: self waterTower.
	
	
	aCollectionOfZones do: [ :aZone | 
		aCity addZone: aZone.
		].
		
	^aCity.! !

!CityTest methodsFor: 'city creation' stamp: 'jpm 9/23/2021 18:41:37'!
cityWithServices: aCollectionOfServices andZones: aCollectionOfZones

	| aCity |
	
	aCity := City new.
	
	aCollectionOfServices do: [ :aService |
		aCity addService: aService.
		].
	
	aCollectionOfZones do: [ :aZone | 
		aCity addZone: aZone.
		].
		
	^aCity.! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'CityTest class' category: 'ISW1-2021-2C-1erParcial'!
CityTest class
	instanceVariableNames: ''!

!CityTest class methodsFor: 'initialization' stamp: 'FRT 9/22/2021 19:22:41'!
initialize

	"Este m�todo est� para crear unidades"
	"No lo deben tocar ni darle importancia durante el parcial"
	
	| ep wp |
	ep := BaseUnit named: 'energypoint' sign: 'ep'.
	wp := BaseUnit named: 'waterpoint' sign: 'wp'.
	
	Smalltalk at: #ep put: ep.
	Smalltalk at: #wp put: wp.! !


!classDefinition: #City category: 'ISW1-2021-2C-1erParcial'!
Object subclass: #City
	instanceVariableNames: 'zones services'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!City methodsFor: 'initialization' stamp: 'jpm 9/23/2021 17:32:35'!
initialize

	services _ OrderedCollection new.
	zones _ OrderedCollection new.! !


!City methodsFor: 'assertions' stamp: 'jpm 9/23/2021 19:42:25'!
assertCityHasResidentialZonesBeforeAddingACommercialZone

	^ self hasResidentialZones ifFalse: [ self error: City cannotAddCommertialZoneErrorDescription ]! !

!City methodsFor: 'assertions' stamp: 'jpm 9/23/2021 20:54:42'!
assertZoneDoesNotExceedEnergySupply: zoneClass

	^ self energyAvailable < zoneClass new energyConsumptionPerCell ifTrue: [ self error: City cannotAddZoneErrorDescription ]! !

!City methodsFor: 'assertions' stamp: 'jpm 9/23/2021 19:39:31'!
assertZoneDoesNotExceedSupplies: zoneClass

	self assertZoneDoesNotExceedEnergySupply: zoneClass.
	self assertZoneDoesNotExceedWaterSupply: zoneClass
	! !

!City methodsFor: 'assertions' stamp: 'jpm 9/23/2021 20:53:51'!
assertZoneDoesNotExceedWaterSupply: zoneClass

	^ self waterAvailable < zoneClass new waterConsumptionPerCell ifTrue: [ self error: City cannotAddZoneErrorDescription ]! !


!City methodsFor: 'modifiers' stamp: 'jpm 9/23/2021 17:31:25'!
addService: aService 

	services add: aService.! !

!City methodsFor: 'modifiers' stamp: 'jpm 9/23/2021 19:45:32'!
addZone: aZone

	aZone addTo: self.
	zones add: aZone.
! !


!City methodsFor: 'private - zone actions' stamp: 'jpm 9/23/2021 19:42:25'!
addCommercialZone

	self assertZoneDoesNotExceedSupplies: Commercial.
	self assertCityHasResidentialZonesBeforeAddingACommercialZone.
	! !

!City methodsFor: 'private - zone actions' stamp: 'jpm 9/23/2021 19:39:55'!
addIndustrialZone
	
	self assertZoneDoesNotExceedEnergySupply: Industrial.
	! !

!City methodsFor: 'private - zone actions' stamp: 'jpm 9/23/2021 19:40:57'!
addResidentialZone

	self assertZoneDoesNotExceedSupplies: Residential.
! !


!City methodsFor: 'supplies testing' stamp: 'FRT 9/16/2021 21:06:00'!
energyAvailable
	
	^ self energyProduced - self energyConsumption

! !

!City methodsFor: 'supplies testing' stamp: 'jpm 9/23/2021 20:54:46'!
energyConsumption
	
	^zones sum: [ :zone | zone energyConsumptionPerCell * zone getNumberOfCells ] ifEmpty: [0 * ep].! !

!City methodsFor: 'supplies testing' stamp: 'jpm 9/23/2021 20:49:12'!
energyProduced
	
	^(services select: [ :service | service isKindOf: SolarPlant])
		sum: [ :service | service production] ifEmpty: [0 * ep].! !

!City methodsFor: 'supplies testing' stamp: 'FRT 9/16/2021 21:23:24'!
waterAvailable
	
	^ self waterProduced - self waterConsumption.! !

!City methodsFor: 'supplies testing' stamp: 'jpm 9/23/2021 20:54:12'!
waterConsumption
	
	^zones sum: [ :zone | zone waterConsumptionPerCell * zone getNumberOfCells ] ifEmpty: [0 * wp].! !

!City methodsFor: 'supplies testing' stamp: 'jpm 9/23/2021 20:49:17'!
waterProduced
	
	^(services select: [ :service | service isKindOf: WaterTower])
		sum: [ :service | service production] ifEmpty: [0 * wp].! !


!City methodsFor: 'zones testing' stamp: 'jpm 9/23/2021 19:45:48'!
hasResidentialZones


	^zones anySatisfy: [ :zone | zone isKindOf:  Residential].! !

!City methodsFor: 'zones testing' stamp: 'jpm 9/23/2021 17:33:15'!
zones

	^ zones.
! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

!classDefinition: 'City class' category: 'ISW1-2021-2C-1erParcial'!
City class
	instanceVariableNames: ''!

!City class methodsFor: 'error descriptions' stamp: 'FRT 9/16/2021 22:10:50'!
cannotAddCommertialZoneErrorDescription

	^ 'Cannot add commertial zone without Residential zones'.! !

!City class methodsFor: 'error descriptions' stamp: 'FRT 9/16/2021 21:41:32'!
cannotAddZoneErrorDescription

	^ 'Cannot add zone'.! !


!classDefinition: #Service category: 'ISW1-2021-2C-1erParcial'!
Object subclass: #Service
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!Service methodsFor: 'production' stamp: 'jpm 9/23/2021 20:48:17'!
production

	self subclassResponsibility.! !


!classDefinition: #SolarPlant category: 'ISW1-2021-2C-1erParcial'!
Service subclass: #SolarPlant
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!SolarPlant methodsFor: 'production' stamp: 'jpm 9/23/2021 20:48:02'!
production

	^ 500 * ep.! !


!classDefinition: #WaterTower category: 'ISW1-2021-2C-1erParcial'!
Service subclass: #WaterTower
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!WaterTower methodsFor: 'production' stamp: 'jpm 9/23/2021 20:48:54'!
production

	^ 200 * wp.  ! !


!classDefinition: #Zone category: 'ISW1-2021-2C-1erParcial'!
Object subclass: #Zone
	instanceVariableNames: 'numberOfCells'
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!Zone methodsFor: 'initialization' stamp: 'jpm 9/23/2021 18:31:39'!
initialize

	numberOfCells := 1.! !


!Zone methodsFor: 'accessing' stamp: 'jpm 9/23/2021 17:25:58'!
getNumberOfCells
	
	^ numberOfCells! !

!Zone methodsFor: 'accessing' stamp: 'HAW 9/23/2021 11:05:04'!
setNumberOfCells: aNumberOfCells
	
	numberOfCells _ aNumberOfCells! !


!Zone methodsFor: 'private - actions' stamp: 'jpm 9/23/2021 18:19:53'!
addTo: aCity
	
	self subclassResponsibility.! !


!Zone methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:49:59'!
energyConsumptionPerCell
	
	self subclassResponsibility.! !

!Zone methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:50:21'!
waterConsumptionPerCell
	
	self subclassResponsibility.! !


!classDefinition: #Commercial category: 'ISW1-2021-2C-1erParcial'!
Zone subclass: #Commercial
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!Commercial methodsFor: 'private - actions' stamp: 'jpm 9/23/2021 19:40:33'!
addTo: aCity
	
	^aCity addCommercialZone.! !


!Commercial methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:51:06'!
energyConsumptionPerCell
	
	^ 8 * ep.! !

!Commercial methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:50:46'!
waterConsumptionPerCell
	
	^ 2 * wp.! !


!classDefinition: #Industrial category: 'ISW1-2021-2C-1erParcial'!
Zone subclass: #Industrial
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!Industrial methodsFor: 'private - actions' stamp: 'jpm 9/23/2021 18:21:20'!
addTo: aCity

	^aCity addIndustrialZone.
	! !


!Industrial methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:51:57'!
energyConsumptionPerCell
	
	^ 10 * ep. ! !

!Industrial methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:51:38'!
waterConsumptionPerCell
	
	^ 10 * wp.  ! !


!classDefinition: #Residential category: 'ISW1-2021-2C-1erParcial'!
Zone subclass: #Residential
	instanceVariableNames: ''
	classVariableNames: ''
	poolDictionaries: ''
	category: 'ISW1-2021-2C-1erParcial'!

!Residential methodsFor: 'private - actions' stamp: 'jpm 9/23/2021 19:32:11'!
addTo: aCity

	^aCity addResidentialZone.! !


!Residential methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:53:10'!
energyConsumptionPerCell
	
	^ 5 * ep. ! !

!Residential methodsFor: 'consumption' stamp: 'jpm 9/23/2021 20:53:30'!
waterConsumptionPerCell
	
	^ 9 * wp. ! !

CityTest initialize!