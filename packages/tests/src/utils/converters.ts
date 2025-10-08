export interface IVector {
  size(): number;
  get(index: number): unknown;
}
export function vectorToArray(vec: IVector): string[] {
  const result: string[] = [];
  for (let i = 0; i < vec.size(); i++) {
    const item = vec.get(i);
    if (item !== undefined) {
      result.push(item as string);
    }
  }
  return result;
}
