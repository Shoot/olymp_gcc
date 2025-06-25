<#assign maxN = 5>
<#assign maxQ = 5>
<#assign minX_maxX = [
  [1, 5],
  [1, 500],
  [999900000, 1000000000]
]>
<#assign tree_vals = [
  -500000,
  -10000,
  -1000,
  -100,
  -10,
  -1,
  0,
  1,
  10,
  100,
  1000,
  10000,
  500000
]>
<#list 1..5 as power>
    <#assign maxN = maxN * 10>
    <#assign maxQ = maxQ * 10>
    <#list 0..2 as i>
        <#list tree_vals as tree>
            g -tree ${tree} -min-n ${maxN} -max-n ${maxN} -min-q ${maxQ} -max-q ${maxQ} -min-x ${minX_maxX[i][0]} -max-x ${minX_maxX[i][1]} > $
        </#list>
    </#list>
</#list>