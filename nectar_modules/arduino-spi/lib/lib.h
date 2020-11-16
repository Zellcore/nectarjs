/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

 #include "SPI.h"

 function __NJS_BEGIN_TRANSACTION (NJS::VAR _v1, NJS::VAR _v2, NJS::VAR _v3)
{ 
	SPI.beginTransaction(SPISettings(__NJS_Get_Int(_v1), __NJS_Get_Int(_v2), __NJS_Get_Int(_v3)));
	return NJS::VAR();
};
 
 function __NJS_END_TRANSACTION (NJS::VAR _v1, NJS::VAR _v2, NJS::VAR _v3)
{ 
	return NJS::VAR();
};

 function __NJS_TRANSFER (NJS::VAR _v1, NJS::VAR _v2, NJS::VAR _v3)
{ 
	return NJS::VAR();
};