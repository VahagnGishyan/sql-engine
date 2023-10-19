
from sqlinterp.conditions import ConditionExecutor
from sqlinterp.conditions import And, Or, Not
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import GreaterThan, GreaterThanOrEqualTo
from sqlinterp.conditions import LessThan, LessThanOrEqualTo


def get_next_condition_operands(tokens: list):
    column_name = tokens.pop()
    value = tokens.pop()
    return (column_name, value, tokens)


def get_next_condition(tokens: list):
    token = tokens.pop()

    if token == 'and':
        tokens, condition = get_next_condition(tokens)
        tokens, second_condition = get_next_condition(tokens)
        return (tokens, And(condition, second_condition))
    elif token == 'or':
        tokens, condition = get_next_condition(tokens)
        tokens, second_condition = get_next_condition(tokens)
        return (tokens, Or(condition, second_condition))
    elif token == 'not':
        tokens, condition = get_next_condition(tokens)
        return (tokens, Not(condition))

    column_name, value, tokens = get_next_condition_operands(tokens)

    if token == '==':
        return (tokens, ConditionExecutor(column_name, Equal(value)))
    elif token == '!=':
        return (tokens, ConditionExecutor(column_name, NotEqual(value)))
    elif token == '>':
        return (tokens, ConditionExecutor(column_name, GreaterThan(value)))
    elif token == '>=':
        return (tokens, ConditionExecutor(column_name, GreaterThanOrEqualTo(value)))
    elif token == '<':
        return (tokens, ConditionExecutor(column_name, LessThan(value)))
    elif token == '<=':
        return (tokens, ConditionExecutor(column_name, LessThanOrEqualTo(value)))
    else:
        raise ValueError(f"Unsupported token: {token}")


def get_condition(tokens: list):
    tokens, condition = get_next_condition(tokens)
    if tokens:
        raise Exception("tokens is not empty.")
    return condition


# Provided list
tokens = ['and', '==', 'a0', '0', 'or', '>=', 'a1', '1', '<=', 'a2', '2']

tokens.reverse()
condition = get_condition(tokens)

condition.print()
